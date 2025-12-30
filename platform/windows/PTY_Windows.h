#pragma once
#include "kterm/PTY.h"

class PTY_Windows : public PTY {
public:
    PTY_Windows();
    void write(const std::string& data) override;
    std::vector<char> read() override;

private:
    void* hPipeIn;
    void* hPipeOut;
};