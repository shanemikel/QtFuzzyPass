#pragma once

#include <QDir>
#include <QMap>

namespace util {
    class NoPasswordStore : public std::runtime_error {
    public:
        NoPasswordStore();
    };

    QDir getPasswordStore();
    QMap<QString, QFileInfo> makePasswordMap(const QDir& passwordStore);
}
