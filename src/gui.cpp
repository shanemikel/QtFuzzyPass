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

        auto passwords =
            QStringList(util::makePasswordMap(util::getPasswordStore()).keys());
        window.setPasswords(passwords);

        window.show();
        return app.exec();
    }

    Window::Window(const QString& title, QWidget* parent) : QWidget(parent) {
        setWindowTitle(title);

        layout = new QVBoxLayout();

        searchBar = new QLineEdit(this);
        searchBar->setAlignment(Qt::AlignHCenter);
        layout->addWidget(searchBar);

        passList = new QListWidget(this);
        layout->addWidget(passList);

        setLayout(layout);

        connect(searchBar, SIGNAL (textChanged(const QString&)),
                this, SLOT (search(const QString&)));
    }

    Window::~Window() {
        // cerr << "Deleting main window." << endl;

        delete finder;
        delete layout;
        delete searchBar;

        while (passList->count() != 0) {
            auto item = passList->takeItem(0);
            delete item;
        }
        delete passList;
    }

    void Window::resize(int width, int height) {
        QWidget::resize(width, height);
        move(QApplication::desktop()->screen()->rect().center() - rect().center());
    }

    void Window::setPasswords(const QStringList& passwords) {
        finder = new Fuzzy(passwords);
        setList(finder->match(""));
    }

    void Window::setList(const QStringList& newList) {
        while (passList->count() != 0) {
            auto item = passList->takeItem(0);
            delete item;
        }
        for (const auto& pass : newList) {
            passList->addItem(pass);
            passList->item(passList->count() - 1)->setTextAlignment(Qt::AlignRight);
        }
        selected_row = 0;
        passList->setCurrentRow(selected_row);
    }

    void Window::keyPressEvent(QKeyEvent* event) {
        switch (event->key()) {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_Up:
            if (selected_row > 0) {
                selected_row -= 1;
                passList->setCurrentRow(selected_row);
            }
            break;
        case Qt::Key_Down:
            if (selected_row < (passList->count() - 1)) {
                selected_row += 1;
                passList->setCurrentRow(selected_row);
            }
            break;
        case Qt::Key_Return:
            if (passList->currentItem() != Q_NULLPTR) {
                QMessageBox passMsg;
                passMsg.setText("Copying password to clipboard:");
                passMsg.setInformativeText(passList->currentItem()->text());
                passMsg.setStandardButtons(QMessageBox::Abort);
                passMsg.exec();
            } else {
                cerr << "No current item selected..." << endl;
            }
            break; 
        default:
            QWidget::keyPressEvent(event);
            break;
        }
    }

    void Window::search(const QString& searchString) {
        setList(finder->match(searchString));
    }
}
