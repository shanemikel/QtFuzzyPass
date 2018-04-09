#include <fuzzy.hpp>

using namespace std;

Fuzzy::Fuzzy(const QStringList& strings)
    : strings(strings)
{}

QStringList Fuzzy::match(const QString& searchString) const {
    struct Match {
        QString item;
        int capturedLength;
    };
    QList<Match> tmp;

    QRegExp regx = fromString(searchString);
    for (auto string : strings) {
        int pos = regx.indexIn(string);
        if (pos > -1) {
            struct Match match;
            match.item = string;
            match.capturedLength = regx.cap(0).size();
            tmp += match;
        }
    }

    sort(tmp.begin(), tmp.end(),
         [](struct Match m1, struct Match m2) {
             if (m1.capturedLength < m2.capturedLength)
                 return true;
             else if (m2.capturedLength < m1.capturedLength)
                 return false;
             else
                 return m1.item < m2.item;
         });

    QStringList res;
    for (auto t : tmp)
        res += t.item;

    return res;
}

QRegExp Fuzzy::fromString(const QString& string) const {
    QString tmp;
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

