#include <gui.hpp>

#include <iostream>
#include <thread>
#include <chrono>

#include <util.hpp>

namespace gui {
    using namespace std;

    int main(QApplication& app, const QStringList&) {
        Window window ("QtFuzzyPass");
        window.setWindowIcon(QIcon(":/icons/key.png"));
        window.resize(500, 350);
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
    }

    void Window::search(const QString& search_string) {
        setList(finder->match(search_string));
    }
}
