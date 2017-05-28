
#include "inc/main.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("QtFuzzyPass");

    QCommandLineParser parser;
    parser.setApplicationDescription("A fuzzy-finder interface to password-store!");
    parser.addHelpOption();

    parser.addOptions({
            {"test",
                    QCoreApplication::translate("main", "A simple testing interface")},
        });
    parser.process(app);

    if (parser.isSet("test"))
        return test::main(parser.positionalArguments());
    else
        return 0;
}
