
#include "inc/test.h"

int test::main(const QStringList & patterns)
{
    QDir passwordStore = QDir(QDir().homePath() + "/.password-store");

    if (passwordStore.exists()) {

        QMap<QString, QFileInfo> passwordMap = makePasswordMap(passwordStore);
        QStringList passwords = QStringList(passwordMap.keys());

        testFuzzy(passwords, patterns);

        return 0;
    } else {

        std::cout << "ERR: ~/.password-store doesn't exist" << std::endl;

        return 1;
    }
}

void test::testFuzzy(const QStringList & passwds, const QStringList & pattns)
{
    if (pattns.size() == 0) {
        for (auto passwd : passwds)
            std::cout << qPrintable(QString("%1").arg(passwd)) << std::endl;
    } else {
        Fuzzy fz = Fuzzy(passwds);
        for (auto pattn : pattns) {
            std::cout << qPrintable(pattn) << std::endl;

            QStringList res = fz.match(pattn);
            if (! res.size())
                continue;
            for (auto r : res)
                std::cout << "    " << qPrintable(r) << std::endl;
        }
    }
}

QMap<QString, QFileInfo> test::makePasswordMap(const QDir & passwordStore)
{
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
