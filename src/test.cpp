#include "test.hpp"

#include <iostream>

#include "fuzzy.hpp"
#include "util.hpp"

namespace test {
    using namespace std;

    int main(const QStringList& patterns) {
        QStringList passwords = util::makePasswordMap(util::getPasswordStore()).keys();
        fuzzy(passwords, patterns);

        return 0;
    }

    void fuzzy(const QStringList& passwds, const QStringList& pattns) {
        if (pattns.size() == 0) {
            for (auto passwd : passwds)
                cout << qPrintable(QString("%1").arg(passwd)) << endl;
        } else {
            Fuzzy fz = Fuzzy(passwds);
            for (auto pattn : pattns) {
                cout << qPrintable(pattn) << endl;

                QStringList res = fz.match(pattn);
                if (! res.size())
                    continue;
                for (auto r : res)
                    cout << "    " << qPrintable(r) << endl;
            }
        }
    }
}
