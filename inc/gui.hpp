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

        void resize(int width, int height);
        void setPasswords(const QStringList& passwords);
        void setList(const QStringList& new_list);

    private:
        int selected_row = 0;
        Fuzzy* finder;

        QVBoxLayout* layout = Q_NULLPTR;
        QLineEdit* search_bar = Q_NULLPTR;
        QListWidget* pass_list = Q_NULLPTR;

    public:
        virtual void keyPressEvent(QKeyEvent* event) override;

    private slots:
        void search(const QString& search_string);
    };
}
