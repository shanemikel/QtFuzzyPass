
#include "inc/cli.h"

int cli::main(const QStringList & patterns)
{
    if (patterns.size() != 1) {
        std::cerr << "ERR: Expecting exaclty one pattern argument" << std::endl;
        return 1;
    }

    std::cout << "Not implemented" << std::endl;
    return 1;
}
