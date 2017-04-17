
#include "inc/fuzzy.h"

Fuzzy::Fuzzy(QStringList *strings)
{
    this->strings = strings;
}

Fuzzy::~Fuzzy()
{
    // TODO learn how to do GC in Qt
    //
    // if (strings)
    //     delete strings;
}

QStringList* Fuzzy::match(QString const searchString)
{
    struct Match
    {
        QString item;
        int capturedLength;
    };
    QList<Match> tmp;

    QRegExp regx = *fromString(searchString);
    for (int i = 0; i < strings->size(); ++i) {
        QString string = strings->at(i);
        int pos = regx.indexIn(string);
        if (pos > -1) {
            struct Match match;
            match.item = string;
            match.capturedLength = regx.cap(0).size();
            tmp << match;
        }
    }

    std::sort(tmp.begin(), tmp.end(), [](struct Match m1, struct Match m2) {
            if (m1.capturedLength < m2.capturedLength)
                return true;
            else if (m2.capturedLength < m1.capturedLength)
                return false;
            else
                return m1.item < m2.item;
        });

    QStringList *res = new QStringList();
    for (int i = 0; i < tmp.size(); ++i)
        *res << tmp.at(i).item;

    return res;
}

QRegExp* Fuzzy::fromString(QString const string)
{
    QString tmp;

    QString::const_iterator i;
    for (i = string.cbegin(); i != string.end(); ++i) {
        tmp.append(*i);
        tmp.append("*");
    }
    if (tmp.length() >= 1)
        tmp.remove(tmp.length()-1, 1);

    QRegExp *regx = new QRegExp();
    regx->setPatternSyntax(QRegExp::Wildcard);
    regx->setMinimal(true);
    regx->setPattern(tmp);
    return regx;
}

