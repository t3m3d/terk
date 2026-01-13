#pragma once
#include <QMainWindow>
#include "TerminalWidget.hpp"
#include "kterm/Config.hpp"

namespace kterm::ui {

class TerminalWindow : public QMainWindow {
public:
    explicit TerminalWindow(const kterm::Config& config)
        : m_config(config)
    {
        setWindowTitle("terk");

        // Pass config into TerminalWidget
        setCentralWidget(new TerminalWidget(m_config, this));

        resize(800, 600);
    }

private:
    kterm::Config m_config;
};

}