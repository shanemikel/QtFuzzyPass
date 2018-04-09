#include <QtWidgets>
#include <QCommandLineParser>
#include <iostream>

#include <test.hpp>
#include <cli.hpp>
#include <gui.hpp>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName("QtFuzzyPass");

    QCommandLineParser parser;
    parser.setApplicationDescription("A fuzzy-finder interface to password-store!");
    parser.addHelpOption();

    parser.addOptions({
            {{"t", "test"}, app.translate("main", "A simple testing interface")},
            {{"c", "cli"},  app.translate("main", "Command line interface")},
            {{"g", "gui"},  app.translate("main", "Graphic interface")}
        });
    parser.process(app);

    if (parser.isSet("test"))
        return test::main(parser.positionalArguments());
    else if (parser.isSet("cli"))
        return cli::main(parser.positionalArguments());
    else if (parser.isSet("gui"))
        return gui::main(app, parser.positionalArguments());
    else
        return 1;
}
