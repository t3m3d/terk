#include "kterm/input/InputHandler.hpp"

using namespace kterm::input;

void InputHandler::handleKey(int keyCode, Modifier mod) {
    // Translate and send to PTY
}

void InputHandler::handleMouse(int x, int y, bool leftClick) {
    // Optional: send mouse events to terminal
}

std::string InputHandler::translateToEscape(int keyCode, Modifier mod) {
    // Return ANSI escape sequence for key
    return {};
}