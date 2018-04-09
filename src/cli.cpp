#include <cli.hpp>

#include <QProcess>
#include <iostream>

#include <fuzzy.hpp>

namespace cli {
    int main(const QStringList& patterns) {
        if (patterns.size() != 1) {
            std::cerr << "Error: expecting exaclty one pattern argument" << std::endl;
            return 1;
        }

        QProcess pass;
        pass.start("pass", QStringList() << "--help");
        if (! pass.waitForStarted() || ! pass.waitForFinished())
            return 1;
        std::cout << qPrintable(pass.readAll());

        return 0;
    }
}
