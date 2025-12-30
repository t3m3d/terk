#include "kterm/TerminalWindow.h"
#include "kterm/TerminalWidget.h"

TerminalWindow::TerminalWindow() {
    terminal = std::make_unique<TerminalWidget>();
}

void TerminalWindow::show() {
    // Placeholder: integrate with Qt or your chosen UI toolkit
}