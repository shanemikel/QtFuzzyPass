
#include "inc/fuzzy.h"

Fuzzy::Fuzzy(const Fuzzy & other)
    : strings_(other.strings_)
{
}

Fuzzy::Fuzzy(Fuzzy && other)
    : strings_(other.strings_)
{
}

// Fuzzy::operator=(const Fuzzy & other)
// {
// }

// Fuzzy::operator=(Fuzzy && other)
// {
// }

Fuzzy::Fuzzy(const QStringList & strings)
    : strings_(strings)
{
}

Fuzzy::Fuzzy(QStringList && strings)
    : strings_(strings)
{
}

// Fuzzy::~Fuzzy()
// {
// }

QStringList Fuzzy::match(const QString searchString) const
{
    struct Match
    {
        QString item;
        int capturedLength;
    };
    QList<Match> tmp;

    QRegExp regx = fromString(searchString);
    // for (int i = 0; i != strings.size(); ++i) {
    //     QString string = strings.at(i);
    for (auto string : strings_) {
        int pos = regx.indexIn(string);
        if (pos > -1) {
            struct Match match;
            match.item = string;
            match.capturedLength = regx.cap(0).size();
            tmp += match;
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

    QStringList res;
    // for (int i = 0; i < tmp.size(); ++i)
    //     res << tmp.at(i).item;
    for (auto t : tmp)
        res += t.item;

    return res;
}

QRegExp Fuzzy::fromString(const QString string) const
{
    QString tmp;
    // QString::const_iterator i;
    // for (i = string.cbegin(); i != string.end(); ++i) {
    //     tmp.append(*i);
    //     tmp.append("*");
    // }
    for (auto c : string) {
        tmp += c;
        tmp += "*";
    }
    if (tmp.length() >= 1)
        tmp.remove(tmp.length()-1, 1);

    QRegExp regx;
    regx.setPatternSyntax(QRegExp::Wildcard);
    regx.setMinimal(true);
    regx.setPattern(tmp);
    return regx;
}

