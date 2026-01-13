#pragma once
#include <vector>
#include "Cell.hpp"

namespace kterm::renderer {

class Grid {
public:
    Grid(int cols, int rows);

    void resize(int cols, int rows);
    void clear();
    void clearLine();

    void putChar(char c);

    void cursorUp(int n);
    void cursorDown(int n);
    void cursorForward(int n);
    void cursorBack(int n);
    void setCursor(int row, int col);

    const std::vector<std::vector<Cell>>& rows() const;

private:
    int m_cols;
    int m_rows;
    int m_cursorRow;
    int m_cursorCol;

    std::vector<std::vector<Cell>> m_cells;

    void clampCursor();
};

}