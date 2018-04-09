#pragma once

#include <QStringList>
#include <QRegExp>
#include <iostream>

class Fuzzy {
private:
    const QStringList strings;

    QRegExp fromString(const QString& string) const;

public:
    Fuzzy(const QStringList& strings);

    QStringList match(const QString& searchString) const;
};
