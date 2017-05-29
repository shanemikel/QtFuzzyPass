
#ifndef TEST_H
#define TEST_H

#include "inc/fuzzy.h"
#include "inc/util.h"

#include <iostream>

namespace test {
    int main(const QStringList & patterns);

    void testFuzzy(const QStringList & passwds, const QStringList & pattns);
}

#endif TEST_H
