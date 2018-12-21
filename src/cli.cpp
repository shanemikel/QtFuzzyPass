#include <cli.hpp>

#include <QProcess>
#include <iostream>

namespace cli {
    using namespace std;

    int main(const QStringList& patterns) {
        if (patterns.size() != 1) {
            cerr << "Error: expecting exaclty one pattern argument" << endl;
            return 1;
        }

        QProcess pass;
        pass.start("pass", QStringList() << "--help");
        if (! pass.waitForStarted() || ! pass.waitForFinished())
            return 1;
        cout << qPrintable(pass.readAll());

        return 0;
    }
}
