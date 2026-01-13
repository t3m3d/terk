#include "TerminalWindow.hpp"
#include "TerminalWidget.hpp"

namespace kterm::ui {

TerminalWindow::TerminalWindow(const kterm::Config& config)
    : m_config(config)
{
    setWindowTitle("terk");

    // Pass config into TerminalWidget
    setCentralWidget(new TerminalWidget(m_config, this));

    resize(800, 600);
}

}