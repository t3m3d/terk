#include <QApplication>
#include "kterm/ui/TerminalWindow.hpp"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    kterm::ui::TerminalWindow win;
    win.show();

    return app.exec();
}