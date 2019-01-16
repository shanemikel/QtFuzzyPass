#include "util.hpp"

#include <QRegExp>
#include <algorithm>
#include <QProcess>

namespace util {
    FuzzyFinder::FuzzyFinder(const QStringList& strings) : strings(strings) {}

    QStringList FuzzyFinder::match(const QString& searchString) const {
        struct Match {
            QString item;
            int capturedLength;
        };
        QList<Match> tmp;

        auto regx = patternFromString(searchString);
        for (auto string : strings) {
            int pos = regx.indexIn(string);
            if (pos > -1) {
                struct Match match;
                match.item = string;
                match.capturedLength = regx.cap(0).size();
                tmp += match;
            }
        }

        std::sort(tmp.begin(), tmp.end(),
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

    QRegExp FuzzyFinder::patternFromString(const QString& string) const {
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

    QDir getPasswordStore() {
        QDir passwordStore = QDir(QDir().homePath() + "/.password-store");
        if (! passwordStore.exists())
            throw "No password store available at ~/.password-store";

        return passwordStore;
    }

    QMap<QString, QFileInfo> makePasswordMap(const QDir& passwordStore) {
        QMap<QString, QFileInfo> map;
        QList<QDir> dirs;
        dirs += passwordStore;

        for (int i = 0; i != dirs.size(); ++i) {
            QDir currentDir = dirs.at(i);
            QFileInfoList infoLst;

            currentDir.setFilter(QDir::Files);
            infoLst = currentDir.entryInfoList();
            for (auto fileInfo : infoLst) {
                if (fileInfo.suffix() != "gpg")
                    continue;

                QString dir = fileInfo.dir().absolutePath();
                QString file = fileInfo.completeBaseName();
                QString name = dir.split(passwordStore.absolutePath()).at(1);
                name = name.remove(0, 1) + "/" + file;
                map.insert(name, fileInfo);
            }

            currentDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
            infoLst = currentDir.entryInfoList();
            for (auto dirInfo : infoLst)
                dirs.append(QDir(dirInfo.filePath()));
        }
        return map;
    }

    int copyPasswordToClipboard(const QString& relpath) {
        QProcess pass;
        pass.start("pass", QStringList() << "-c" << relpath);

        if (! pass.waitForStarted() || ! pass.waitForFinished())
            return 1;

        return pass.exitCode();
    }
}
