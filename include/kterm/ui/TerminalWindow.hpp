#pragma once
#include <QMainWindow>
#include "TerminalWidget.hpp"

namespace kterm::ui {

class TerminalWindow : public QMainWindow {
public:
    TerminalWindow() {
        setWindowTitle("terk");
        setCentralWidget(new TerminalWidget(this));
        resize(800, 600);
    }
};

}