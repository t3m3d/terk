#pragma once
#include <QWidget>
#include <QTimer>
#include "kterm/core/Terminal.hpp"
#include "kterm/renderer/QtRenderer.hpp"
#include "kterm/input/InputHandler.hpp"
#include "kterm/pty/PTY.hpp"

namespace kterm::ui {

class TerminalWidget : public QWidget {
    Q_OBJECT

public:
    TerminalWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void resizeEvent(QResizeEvent*) override;

private:
    core::Terminal m_terminal;
    renderer::QtRenderer* m_renderer = nullptr;
    input::InputHandler m_input;
    pty::PTY m_pty;

    int m_cellWidth = 8;
    int m_cellHeight = 16;

    void setupPTY();
    void setupRenderer();
};

}