#include <QtWidgets>
#include <QCommandLineParser>
#include <iostream>

#include <test.hpp>
#include <cli.hpp>
#include <gui.hpp>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName("pass-qt");

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt fuzzy-finder interface to password-store");
    parser.addHelpOption();

    parser.addOptions({
            {{"t", "test"}, app.translate("main", "Testing interface")},
            {{"c", "cli"},  app.translate("main", "Command line interface")},
            {{"g", "gui"},  app.translate("main", "Graphic interface")}
        });
    parser.process(app);

    if (parser.isSet("test")) {
        return test::main(parser.positionalArguments());
    } else if (parser.isSet("cli")) {
        return cli::main(parser.positionalArguments());
    } else {
        return gui::main(app, parser.positionalArguments());
    }
}
