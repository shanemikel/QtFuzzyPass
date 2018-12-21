#pragma once

#include <QtWidgets>
#include <QStringList>

namespace gui {
    class StringListWidget : public QListWidget {
        Q_OBJECT

    public:
        explicit StringListWidget(QWidget* parent = Q_NULLPTR);

    public slots:
        void setList(const QStringList& passwords);
        void selectNext();
        void selectPrevious();

        bool isEmpty();

        QString getCurrent();

    private:
        int selected_row = 0;
    };
}
