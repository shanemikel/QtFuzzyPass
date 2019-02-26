#include <gui.hpp>
#include <util.hpp>
#include <FuzzyFinderWidget.hpp>

#include <iostream>

namespace gui {
    int main(QApplication& app, const QStringList&) {
        Window window;
        window.resize(500, 300);
        window.moveToCenter();

        window.show();
        return app.exec();
    }

    Window::Window(QWidget* parent) : QWidget(parent) {
        setWindowTitle(tr("Password Store"));
        // setWindowIcon(QIcon(":/keychain.iconset/icon_256x256.png"));

        passwords = util::makePasswordMap(util::getPasswordStore());

        auto layout = new QHBoxLayout(this);

        auto fuzzyFinderWidget = new FuzzyFinderWidget(this);
        fuzzyFinderWidget->setList(QStringList(passwords.keys()));
        connect(fuzzyFinderWidget, SIGNAL (itemChosen(const QString&)),
                this, SLOT (copyPassword(const QString&)));
        layout->addWidget(fuzzyFinderWidget);
    }

    void Window::moveToCenter() {
        move(QApplication::desktop()->screen()->rect().center() - rect().center());
    }

    void Window::keyPressEvent(QKeyEvent* event) {
        switch (event->key()) {
        case Qt::Key_Escape:
            close();
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
        }
    }

    void Window::copyPassword(const QString& password) {
        int ret = util::copyPasswordToClipboard(password);

        QMessageBox passMsg;
        if (ret == 0) {
            passMsg.setText(tr("Copied password to clipboard"));
        } else {
            passMsg.setText(tr("An error occurred"));
        }
        passMsg.setStandardButtons(QMessageBox::Ok);
        passMsg.exec();

        close();
    }
}
