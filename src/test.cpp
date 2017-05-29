
#include "inc/test.h"

int test::main(const QStringList & patterns)
{
    QStringList passwords = util::makePasswordMap(util::getPasswordStore()).keys();
    testFuzzy(passwords, patterns);

    return 0;
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
