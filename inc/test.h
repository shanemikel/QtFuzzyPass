
#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <QDir>
#include <QMap>

#include "inc/fuzzy.h"

namespace test {
    int main(const QStringList & patterns);

    QMap<QString, QFileInfo> makePasswordMap(const QDir & passwordStore);
    void testFuzzy(const QStringList & passwds, const QStringList & pattns);
}

#endif TEST_H
