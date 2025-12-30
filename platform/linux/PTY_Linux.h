#pragma once
#include "kterm/PTY.h"

class PTY_Linux : public PTY {
public:
    PTY_Linux();
    void write(const std::string& data) override;
    std::vector<char> read() override;

private:
    int masterFd;
};