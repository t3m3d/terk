#pragma once
#include <memory>

class TerminalWidget;

class TerminalWindow {
public:
    TerminalWindow();
    ~TerminalWindow();
    
    void show();

private:
    std::unique_ptr<TerminalWidget> terminal;
};