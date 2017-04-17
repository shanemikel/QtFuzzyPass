
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
            QString dir = curLst.at(j).dir().absolutePath();
            QString file = curLst.at(j).fileName();
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

void testFuzzy()
{
    QStringList strings;
    strings << "this is a string"
            << "how do you like fuzzy finding?"
            << "/home/spearlman/home/spearlman"
            << "/a/h/o/m/e";
    QStringList patterns;
    patterns << "this"
             << "hing"
             << "home";
    Fuzzy fz = Fuzzy(&strings);
    for (int i = 0; i < patterns.size(); ++i) {
        QStringList res = *fz.match(patterns.at(i));
        std::cout << qPrintable(patterns.at(i))
                  << std::endl;
        for (int j = 0; j < res.size(); ++j)
            std::cout << "    "
                      << qPrintable(res.at(j))
                      << std::endl;
    } 
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // QDir passwordStore = QDir(QDir().homePath() + "/.password-store");
    // QMap<QString, QFileInfo> *passwordMap = makePasswordMap(passwordStore);
    // QList<QString> passwords = passwordMap->keys();

    // for (int i = 0; i < passwords.size(); ++i)
    //     std::cout << qPrintable(QString("%1").arg(passwords.at(i)))
    //               << std::endl;

    testFuzzy();

    return 0;
}
