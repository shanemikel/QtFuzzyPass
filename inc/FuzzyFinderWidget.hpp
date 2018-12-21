#pragma once

#include <util.hpp>
#include <StringListWidget.hpp>

#include <QtWidgets>
#include <QStringList>

namespace gui {
    class FuzzyFinderWidget : public QWidget {
        Q_OBJECT
    public:
        explicit FuzzyFinderWidget(QWidget* parent = Q_NULLPTR);
        virtual ~FuzzyFinderWidget() override;

        void setList(const QStringList& newList);

    private:
        util::FuzzyFinder* fuzzyFinder;
        StringListWidget* listWidget;

    public:
        virtual void keyPressEvent(QKeyEvent* event) override;

    private slots:
        void searchList(const QString& searchString);
        void chooseCurrentItem();

    signals:
        void itemChosen(const QString& item);
    };
}
