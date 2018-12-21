#include <StringListWidget.hpp>

namespace gui {
    StringListWidget::StringListWidget(QWidget* parent) : QListWidget(parent) {}

    void StringListWidget::setList(const QStringList& items) {
        clear();
        for (const auto& item : items) {
            addItem(new QListWidgetItem(item));
        }
        selected_row = 0;
        setCurrentRow(selected_row);
    }

    void StringListWidget::selectNext() {
        if (selected_row < (count() - 1)) {
            selected_row += 1;
            setCurrentRow(selected_row);
        }
    }

    void StringListWidget::selectPrevious() {
        if (selected_row > 0) {
            selected_row -= 1;
            setCurrentRow(selected_row);
        }
    }

    bool StringListWidget::isEmpty() {
        return currentItem() == Q_NULLPTR;
    }

    QString StringListWidget::getCurrent() {
        if (isEmpty())
            throw "Password List is Empty";
        return currentItem()->text();
    }
}
