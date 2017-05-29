
#ifndef UTIL_H
#define UTIL_H

#include <QDir>
#include <QMap>

namespace util {
    QMap<QString, QFileInfo> makePasswordMap(const QDir & passwordStore);
}

#endif UTIL_H
