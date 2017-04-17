
#include "inc/main.h"

QMap<QString, QFileInfo>* makePasswordMap(QDir const passwordStore)
{
    if (! passwordStore.exists())
        return NULL;
    QMap<QString, QFileInfo> *map = new QMap<QString, QFileInfo>();

    QList<QDir> dirs;
    dirs << passwordStore;

    for (int i = 0; i < dirs.size(); ++i) {
        QDir cur = dirs.at(i);
        QFileInfoList curLst;

        cur.setFilter(QDir::Files);
        curLst = cur.entryInfoList();
        for (int j = 0; j < curLst.size(); ++j) {
            if (curLst.at(j).suffix() != "gpg")
                continue;

            QString dir = curLst.at(j).dir().absolutePath();
            QString file = curLst.at(j).completeBaseName();
            QString name = dir.split(passwordStore.absolutePath()).at(1);
            name = name.remove(0, 1) + "/" + file;
            map->insert(name, curLst.at(j));
        }

        cur.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
        curLst = cur.entryInfoList();
        for (int j = 0; j < curLst.size(); ++j)
            dirs.append(QDir(curLst.at(j).filePath()));
    }

    return map;
}

void testFuzzy(QStringList passwds, QStringList pattns)
{
    if (pattns.size() == 0) {
        for (int i = 0; i < passwds.size(); ++i)
            std::cout << qPrintable(QString("%1").arg(passwds.at(i)))
                      << std::endl;
    } else {
        Fuzzy fz = Fuzzy(&passwds);
        for (int i = 0; i < pattns.size(); ++i) {
            std::cout << qPrintable(pattns.at(i))
                      << std::endl;

            QStringList *res;
            if (! (res = fz.match(pattns.at(i))))
                continue;
            for (int j = 0; j < res->length(); ++j)
                std::cout << "    "
                          << qPrintable(res->at(j))
                          << std::endl;
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QStringList patterns;
    for (int i = 1; i < argc; ++i)
        patterns << argv[i];

    QDir passwordStore = QDir(QDir().homePath() + "/.password-store");
    QMap<QString, QFileInfo> *passwordMap = makePasswordMap(passwordStore);
    QStringList passwords = QStringList(passwordMap->keys());

    testFuzzy(passwords, patterns);

    return 0;
}
