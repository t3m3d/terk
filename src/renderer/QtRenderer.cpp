#include "kterm/renderer/QtRenderer.hpp"
#include <QColor>
#include <QFontMetrics>

using namespace kterm::renderer;

QtRenderer::QtRenderer(QPainter* painter, int cellWidth, int cellHeight)
    : m_painter(painter),
      m_cellWidth(cellWidth),
      m_cellHeight(cellHeight) {}

void QtRenderer::drawGrid(const Grid& grid) {
    const auto& rows = grid.rows();

    for (int r = 0; r < (int)rows.size(); ++r) {
        for (int c = 0; c < (int)rows[r].size(); ++c) {
            drawCell(r, c, rows[r][c]);
        }
    }
}

void QtRenderer::drawCell(int row, int col, const Cell& cell) {
    int x = col * m_cellWidth;
    int y = row * m_cellHeight;

    // Background
    m_painter->fillRect(x, y, m_cellWidth, m_cellHeight, QColor(cell.bg));

    // Foreground text
    m_painter->setPen(QColor(cell.fg));
    m_painter->drawText(x, y + m_cellHeight - 2, QString(cell.ch));
}