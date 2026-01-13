#pragma once
#include <QMainWindow>
#include "TerminalWidget.hpp"
#include "kterm/Config.hpp"

namespace kterm::ui {

class TerminalWindow : public QMainWindow {
public:
    explicit TerminalWindow(const kterm::Config& config);

private:
    kterm::Config m_config;
};

}