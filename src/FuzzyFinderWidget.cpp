#include <FuzzyFinderWidget.hpp>
#include <QLineEdit>

#include <iostream>

namespace gui {
    class SearchBarWidget : public QLineEdit {
    public:
        explicit SearchBarWidget(FuzzyFinderWidget* parent = Q_NULLPTR)
            : QLineEdit(parent) {}

        virtual void keyPressEvent(QKeyEvent* event) override {
            switch (event->key()) {
            case Qt::Key_Up:
            case Qt::Key_Down:
            case Qt::Key_Return:
                ((FuzzyFinderWidget*) parentWidget())->keyPressEvent(event);
                break;
            default:
                QLineEdit::keyPressEvent(event);
                break;
            }
        }
    };

    FuzzyFinderWidget::FuzzyFinderWidget(QWidget* parent) : QWidget(parent) {
        fuzzyFinder = nullptr;

        auto mainLayout = new QVBoxLayout(this);

        {
            auto topLayout = new QHBoxLayout();

            auto searchBar = new SearchBarWidget(this);
            connect(searchBar, SIGNAL (textChanged(const QString&)),
                    this, SLOT (searchList(const QString&)));
            topLayout->addWidget(searchBar);

            auto searchButton = new QPushButton(tr("Select"), this);
            connect(searchButton, SIGNAL (pressed()),
                    this, SLOT (chooseCurrentItem()));
            topLayout->addWidget(searchButton);

            mainLayout->addLayout(topLayout);
        }
        
        listWidget = new StringListWidget(this);
        mainLayout->addWidget(listWidget);
    }

    FuzzyFinderWidget::~FuzzyFinderWidget() {
        delete fuzzyFinder;
    }

    void FuzzyFinderWidget::setList(const QStringList& newList) {
        fuzzyFinder = new util::FuzzyFinder(newList);
        listWidget->setList(fuzzyFinder->match(""));
    }

    void FuzzyFinderWidget::keyPressEvent(QKeyEvent* event) {
        switch (event->key()) {
        case Qt::Key_Up:
            listWidget->selectPrevious();
            break;
        case Qt::Key_Down:
            listWidget->selectNext();
            break;
        case Qt::Key_Return:
            chooseCurrentItem();
            break; 
        default:
            QWidget::keyPressEvent(event);
            break;
        }
    }

    void FuzzyFinderWidget::searchList(const QString& searchString) {
        if (fuzzyFinder == nullptr)
            throw "fuzzyFinder == nullptr";

        auto newList = fuzzyFinder->match(searchString);
        listWidget->setList(newList);
    }

    void FuzzyFinderWidget::chooseCurrentItem() {
        if (listWidget->isEmpty()) {
            std::cerr << "FuzzyFinder: no items to choose from empty list"
                      << std::endl;
            return;
        }

        emit itemChosen(listWidget->getCurrent());
    }
}
