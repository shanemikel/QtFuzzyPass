#pragma once

#include <QDir>
#include <QMap>

namespace util {
    class FuzzyFinder {
    public:
        explicit FuzzyFinder(const QStringList& strings);

        QStringList match(const QString& searchString) const;

    private:
        const QStringList strings;
        QRegExp patternFromString(const QString& string) const;
    };

    QDir getPasswordStore();
    QMap<QString, QFileInfo> makePasswordMap(const QDir& passwordStore);
}
