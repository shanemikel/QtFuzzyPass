#pragma once

#include <QtWidgets>
#include <QStringList>
#include <QListWidget>
#include <QLineEdit>

#include <fuzzy.hpp>

namespace gui {
    int main(QApplication& app, const QStringList& args);

    class Window : public QWidget {
        Q_OBJECT
    public:
        explicit Window(const QString& title, QWidget* parent = Q_NULLPTR);
        ~Window() override;

        void resize(int width, int height);
        void setPasswords(const QStringList& passwords);
        void setList(const QStringList& newList);

    private:
        int selected_row = 0;
        Fuzzy* finder;

        QPointer<QVBoxLayout> layout;
        QPointer<QLineEdit> searchBar;
        QPointer<QListWidget> passList;

    public:
        virtual void keyPressEvent(QKeyEvent* event) override;

    private slots:
        void search(const QString& searchString);
    };
}
