
#ifndef UTIL_H
#define UTIL_H

#include <exception>
#include <QDir>
#include <QMap>

namespace util {
    struct NoPasswordStore : public std::runtime_error
    {
        NoPasswordStore();
    };

    QDir getPasswordStore();
    QMap<QString, QFileInfo> makePasswordMap(const QDir & passwordStore);
}

#endif UTIL_H
