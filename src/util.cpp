#include "util.hpp"

#include <exception>
using namespace std;

namespace util {
    NoPasswordStore::NoPasswordStore()
        : runtime_error("No password store available at ~/.password-store")
    {}

    QDir getPasswordStore() {
        QDir passwordStore = QDir(QDir().homePath() + "/.password-store");
        if (! passwordStore.exists())
            throw NoPasswordStore();

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
}
