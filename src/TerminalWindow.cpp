#include "kterm/TerminalWindow.h"
#include "kterm/TerminalWidget.h"

#include <iostream>
#include <conio.h>

TerminalWindow::TerminalWindow() {
    terminal = std::make_unique<TerminalWidget>();
}

TerminalWindow::~TerminalWindow() = default;

void TerminalWindow::show() {
    bool running = true;

    // Clear screen
    std::cout << "\x1b[2J\x1b[H";

    std::cout << "terk is running.\n";
    std::cout << "Press 'q' to quit.\n";

    while (running) {
        if (_kbhit()) {
            int key = _getch();
            if (key == 'q' || key == 'Q') {
                running = false;
            }
        }

        // You can add rendering here later
        // terminal->render();
    }
}

