#include "kterm/ui/TerminalWidget.hpp"
#include <QPainter>
#include <QKeyEvent>

using namespace kterm::ui;

TerminalWidget::TerminalWidget(QWidget* parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);

    setupPTY();
    setupRenderer();

    m_terminal.setRenderCallback([this]() {
        update();
    });
}

void TerminalWidget::setupPTY() {
    m_pty.setOutputCallback([this](const std::vector<char>& data) {
        m_terminal.onPTYOutput(data);
    });

    m_pty.spawnShell("/bin/bash");
}

void TerminalWidget::setupRenderer() {
    // Renderer is created during paintEvent with a QPainter
}

void TerminalWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);

    if (!m_renderer)
        m_renderer = new renderer::QtRenderer(&painter, m_cellWidth, m_cellHeight);

    m_renderer->drawGrid(m_terminal.grid());
}

void TerminalWidget::keyPressEvent(QKeyEvent* e) {
    auto seq = m_input.translateToEscape(e->key(), input::Modifier::None);
    if (!seq.empty())
        m_pty.writeInput(seq);
}

void TerminalWidget::resizeEvent(QResizeEvent*) {
    int cols = width() / m_cellWidth;
    int rows = height() / m_cellHeight;
    m_terminal.resize(cols, rows);
    m_pty.resize(cols, rows);
}