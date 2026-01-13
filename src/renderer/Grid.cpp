#include "kterm/renderer/Grid.hpp"
#include <algorithm>

using namespace kterm::renderer;

Grid::Grid(int cols, int rows)
    : m_cols(cols), m_rows(rows),
      m_cursorRow(0), m_cursorCol(0),
      m_cells(rows, std::vector<Cell>(cols))
{
    // Default colors
    m_currentFG = 0xFFFFFFFF; // white
    m_currentBG = 0xFF000000; // black

    // Standard 16-color palette
    palette16[0]  = 0xFF000000; // black
    palette16[1]  = 0xFFAA0000; // red
    palette16[2]  = 0xFF00AA00; // green
    palette16[3]  = 0xFFAA5500; // yellow
    palette16[4]  = 0xFF0000AA; // blue
    palette16[5]  = 0xFFAA00AA; // magenta
    palette16[6]  = 0xFF00AAAA; // cyan
    palette16[7]  = 0xFFAAAAAA; // white
    palette16[8]  = 0xFF555555; // bright black
    palette16[9]  = 0xFFFF5555; // bright red
    palette16[10] = 0xFF55FF55; // bright green
    palette16[11] = 0xFFFFFF55; // bright yellow
    palette16[12] = 0xFF5555FF; // bright blue
    palette16[13] = 0xFFFF55FF; // bright magenta
    palette16[14] = 0xFF55FFFF; // bright cyan
    palette16[15] = 0xFFFFFFFF; // bright white

    // 256-color palette
    for (int i = 0; i < 256; i++) {
        if (i < 16) {
            palette256[i] = palette16[i];
        } else if (i >= 16 && i < 232) {
            int idx = i - 16;
            int r = (idx / 36) % 6;
            int g = (idx / 6) % 6;
            int b = idx % 6;
            r = r ? r * 40 + 55 : 0;
            g = g ? g * 40 + 55 : 0;
            b = b ? b * 40 + 55 : 0;
            palette256[i] = (0xFF << 24) | (r << 16) | (g << 8) | b;
        } else {
            int gray = (i - 232) * 10 + 8;
            palette256[i] = (0xFF << 24) | (gray << 16) | (gray << 8) | gray;
        }
    }
}

void Grid::resize(int cols, int rows) {
    m_cols = cols;
    m_rows = rows;
    m_cells.assign(rows, std::vector<Cell>(cols));
    m_cursorRow = 0;
    m_cursorCol = 0;
}

void Grid::clear() {
    for (auto& row : m_cells)
        for (auto& cell : row)
            cell = Cell();
}

void Grid::clearLine(int row) {
    if (row >= 0 && row < m_rows)
        m_cells[row].assign(m_cols, Cell());
}

void Grid::putChar(char c) {
    if (c == '\n') {
        m_cursorRow++;
        m_cursorCol = 0;
        clampCursor();
        return;
    }

    if (m_cursorRow < m_rows && m_cursorCol < m_cols) {
        Cell& cell = m_cells[m_cursorRow][m_cursorCol];
        cell.ch = c;
        cell.fg = m_currentFG;
        cell.bg = m_currentBG;
    }

    m_cursorCol++;
    if (m_cursorCol >= m_cols) {
        m_cursorCol = 0;
        m_cursorRow++;
        clampCursor();
    }
}

void Grid::cursorUp(int n) {
    m_cursorRow -= n;
    clampCursor();
}

void Grid::cursorDown(int n) {
    m_cursorRow += n;
    clampCursor();
}

void Grid::cursorForward(int n) {
    m_cursorCol += n;
    clampCursor();
}

void Grid::cursorBack(int n) {
    m_cursorCol -= n;
    clampCursor();
}

void Grid::setCursor(int row, int col) {
    m_cursorRow = row;
    m_cursorCol = col;
    clampCursor();
}

void Grid::setFG16(int index) {
    if (index >= 0 && index < 16)
        m_currentFG = palette16[index];
}

void Grid::setBG16(int index) {
    if (index >= 0 && index < 16)
        m_currentBG = palette16[index];
}

void Grid::setFG256(int index) {
    if (index >= 0 && index < 256)
        m_currentFG = palette256[index];
}

void Grid::setBG256(int index) {
    if (index >= 0 && index < 256)
        m_currentBG = palette256[index];
}

void Grid::setFGTrue(int r, int g, int b) {
    m_currentFG = (0xFF << 24) | (r << 16) | (g << 8) | b;
}

void Grid::setBGTrue(int r, int g, int b) {
    m_currentBG = (0xFF << 24) | (r << 16) | (g << 8) | b;
}

void Grid::resetAttributes() {
    m_currentFG = palette16[7]; // white
    m_currentBG = palette16[0]; // black
}

void Grid::clampCursor() {
    m_cursorRow = std::clamp(m_cursorRow, 0, m_rows - 1);
    m_cursorCol = std::clamp(m_cursorCol, 0, m_cols - 1);
}

const std::vector<std::vector<Cell>>& Grid::rows() const {
    return m_cells;
}