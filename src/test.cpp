#include "test.hpp"
#include "util.hpp"

#include <iostream>

namespace test {
    using namespace std;

    int main(const QStringList& patterns) {
        auto passwords = util::makePasswordMap(util::getPasswordStore()).keys();

        if (patterns.size() == 0) {
            for (auto password : passwords)
                cout << qPrintable(QString("%1").arg(password)) << endl;
        } else {
            util::FuzzyFinder fuzzyFinder(passwords);
            for (auto pattern : patterns) {
                cout << qPrintable(pattern) << endl;

                auto res = fuzzyFinder.match(pattern);
                if (! res.size()) {
                    continue;
                } for (auto r : res) {
                    cout << "    " << qPrintable(r) << endl;
                }
            }
        }

        return 0;
    }
}
