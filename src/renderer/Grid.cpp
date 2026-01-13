#include "kterm/renderer/Grid.hpp"

using namespace kterm::renderer;

Grid::Grid(int cols, int rows)
    : m_cols(cols), m_rows(rows),
      m_cursorRow(0), m_cursorCol(0),
      m_cells(rows, std::vector<Cell>(cols)) {}

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

void Grid::clearLine() {
    if (m_cursorRow >= 0 && m_cursorRow < m_rows)
        m_cells[m_cursorRow].assign(m_cols, Cell());
}

void Grid::putChar(char c) {
    if (c == '\n') {
        m_cursorRow++;
        m_cursorCol = 0;
        clampCursor();
        return;
    }

    if (m_cursorRow < m_rows && m_cursorCol < m_cols)
        m_cells[m_cursorRow][m_cursorCol].ch = c;

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

void Grid::clampCursor() {
    if (m_cursorRow < 0) m_cursorRow = 0;
    if (m_cursorRow >= m_rows) m_cursorRow = m_rows - 1;
    if (m_cursorCol < 0) m_cursorCol = 0;
    if (m_cursorCol >= m_cols) m_cursorCol = m_cols - 1;
}

const std::vector<std::vector<Cell>>& Grid::rows() const {
    return m_cells;
}