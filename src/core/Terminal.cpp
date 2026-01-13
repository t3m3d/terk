#include "kterm/core/Terminal.hpp"
#include "kterm/pty/PTY.hpp"

using namespace kterm::core;

Terminal::Terminal(int cols, int rows)
    : m_grid(cols, rows),
      m_parser(cols, rows)
{
}

void Terminal::setRenderCallback(RenderCallback cb) {
    m_renderCallback = cb;
}

void Terminal::onPTYOutput(const std::vector<char>& data) {
    std::string chunk(data.begin(), data.end());

    m_parser.feed(chunk,
        [&](const std::string& text) {
            applyText(text);
        },
        [&](const parser::EscapeSequence& seq) {
            applyEscape(seq);
        }
    );

    if (m_renderCallback)
        m_renderCallback();
}

void Terminal::applyText(const std::string& text) {
    for (char c : text)
        m_grid.putChar(c);
}

void Terminal::applyEscape(const parser::EscapeSequence& seq) {
    switch (seq.type) {
        case parser::EscapeType::CursorUp:
            m_grid.cursorUp(seq.value);
            break;
        case parser::EscapeType::CursorDown:
            m_grid.cursorDown(seq.value);
            break;
        case parser::EscapeType::CursorForward:
            m_grid.cursorForward(seq.value);
            break;
        case parser::EscapeType::CursorBack:
            m_grid.cursorBack(seq.value);
            break;
        case parser::EscapeType::SetCursorPos:
            m_grid.setCursor(seq.row, seq.col);
            break;
        case parser::EscapeType::ClearScreen:
            m_grid.clear();
            break;
        case parser::EscapeType::ClearLine:
            m_grid.clearLine();
            break;
        default:
            break;
    }
}

void Terminal::writeToPTY(const std::string& input) {
    // This will be connected to PTY::writeInput() by TerminalWidget
}

void Terminal::resize(int cols, int rows) {
    m_grid.resize(cols, rows);
    m_parser.resize(cols, rows);
}

renderer::Grid& Terminal::grid() {
    return m_grid;
}

const renderer::Grid& Terminal::grid() const {
    return m_grid;
}