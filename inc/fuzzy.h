
#ifndef FUZZY_H
#define FUZZY_H

#include <iostream>
#include <QStringList>
#include <QRegExp>

class Fuzzy
{
public:
    Fuzzy(QStringList *strings);
    ~Fuzzy();

    QStringList* match(QString const searchString);

private:
    QRegExp* fromString(QString const string);

    QStringList *strings;
    
};

#endif
