#include <gui.hpp>

#include <iostream>
using namespace std;

#include <util.hpp>

namespace gui {
    using namespace std;

    int main(QApplication& app, const QStringList&) {
        Window window ("QtFuzzyPass");
        window.setWindowIcon(QIcon(":/icons/key.png"));
        window.resize(500, 300);
        window.show();

        auto passwords =
            QStringList(util::makePasswordMap(util::getPasswordStore()).keys());
        window.setPasswords(passwords);

        return app.exec();
    }

    Window::Window(const QString& title, QWidget* parent) : QWidget(parent) {
        setWindowTitle(title);
        layout = new QVBoxLayout;

        search_bar = new QLineEdit(this);
        search_bar->setAlignment(Qt::AlignHCenter);
        layout->addWidget(search_bar);

        pass_list = new QListWidget(this);
        layout->addWidget(pass_list);

        setLayout(layout);

        connect(search_bar, SIGNAL (textChanged(const QString&)),
                this, SLOT (search(const QString&)));
    }

    void Window::resize(int width, int height) {
        QWidget::resize(width, height);
        move(QApplication::desktop()->screen()->rect().center() - rect().center());
    }

    void Window::setPasswords(const QStringList& passwords) {
        finder = new Fuzzy(passwords);
        setList(finder->match(""));
    }

    void Window::setList(const QStringList& new_list) {
        while (pass_list->count() != 0)
            pass_list->takeItem(0);
        for (const auto& pass : new_list) {
            pass_list->addItem(pass);
            pass_list->item(pass_list->count() - 1)->setTextAlignment(Qt::AlignRight);
        }
        selected_row = 0;
        pass_list->setCurrentRow(selected_row);
    }

    void Window::keyPressEvent(QKeyEvent* event) {
        switch (event->key()) {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Up:
            if (selected_row > 0) {
                selected_row -= 1;
                pass_list->setCurrentRow(selected_row);
            }
            break;
        case Qt::Key_Down:
            if (selected_row < (pass_list->count() - 1)) {
                selected_row += 1;
                pass_list->setCurrentRow(selected_row);
            }
            break;
        case Qt::Key_Return:
            if (pass_list->currentItem() != Q_NULLPTR) {
                QMessageBox pass_msg;
                pass_msg.setText("Copying password to clipboard:");
                pass_msg.setInformativeText(pass_list->currentItem()->text());
                pass_msg.setStandardButtons(QMessageBox::Abort);
                pass_msg.exec();
            } else {
                cerr << "No current item selected..." << endl;
            }
            break; 
        default:
            QWidget::keyPressEvent(event);
            break;
        }
    }

    void Window::search(const QString& search_string) {
        setList(finder->match(search_string));
    }
}
