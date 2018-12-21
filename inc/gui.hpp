#pragma once

#include <QtWidgets>
#include <QStringList>
#include <QDir>
#include <QMap>

namespace gui {
    int main(QApplication& app, const QStringList& args);

    class Window : public QWidget {
        Q_OBJECT
    public:
        explicit Window(QWidget* parent = Q_NULLPTR);

        void moveToCenter();

    public:
        virtual void keyPressEvent(QKeyEvent* event) override;

    private slots:
        void copyPassword(const QString& password);

    private:
        QMap<QString, QFileInfo> passwords;
    };
}
