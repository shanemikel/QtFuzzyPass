#pragma once

#include<QtWidgets>
#include<QStringList>
#include<QListWidget>
#include<QLineEdit>

#include <fuzzy.hpp>

namespace gui {
    int main(QApplication& app, const QStringList& args);

    class Window : public QWidget {
        Q_OBJECT
    public:
        explicit Window(const QString& title, QWidget* parent = nullptr);

        void resize(int width, int height);
        void setPasswords(const QStringList& passwords);
        void setList(const QStringList& new_list);

    private:
        Fuzzy* finder;

        QVBoxLayout* layout = nullptr;
        QLineEdit* search_bar = nullptr;
        QListWidget* pass_list = nullptr;

    private slots:
        void search(const QString& search_string);
    };
}
