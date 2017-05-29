
#include "inc/test.h"

int test::main(const QStringList & patterns)
{
    QDir passwordStore = QDir(QDir().homePath() + "/.password-store");

    if (passwordStore.exists()) {

        QMap<QString, QFileInfo> passwordMap = util::makePasswordMap(passwordStore);
        QStringList passwords = QStringList(passwordMap.keys());

        testFuzzy(passwords, patterns);

        return 0;
    } else {

        std::cerr << "ERR: ~/.password-store doesn't exist" << std::endl;

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
