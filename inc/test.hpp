#pragma once

#include <QStringList>

namespace test {
    int main(const QStringList& patterns);

    void fuzzy(const QStringList& passwds, const QStringList& pattns);
}
