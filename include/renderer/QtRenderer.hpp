#pragma once
#include "Renderer.hpp"
#include <QPainter>

namespace kterm::renderer {

class QtRenderer : public Renderer {
public:
    QtRenderer(QPainter* painter, int cellWidth, int cellHeight);

    void drawGrid(const Grid& grid) override;
    void drawCell(int row, int col, const Cell& cell) override;

private:
    QPainter* m_painter;
    int m_cellWidth;
    int m_cellHeight;
};

}