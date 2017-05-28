
#ifndef FUZZY_H
#define FUZZY_H

#include <iostream>
#include <QStringList>
#include <QRegExp>

class Fuzzy
{
public:
    Fuzzy(const Fuzzy & other);
    Fuzzy(Fuzzy && other);

    Fuzzy & operator=(const Fuzzy & other) =delete;
    Fuzzy & operator=(Fuzzy && other) =delete;

    Fuzzy(const QStringList & strings);
    Fuzzy(QStringList && strings);

    QStringList match(const QString searchString) const;

private:
    QRegExp fromString(const QString string) const;

    const QStringList strings_;
};

#endif FUZZY_H
