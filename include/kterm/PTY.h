#pragma once
#include <string>
#include <vector>

class PTY {
public:
    virtual ~PTY() = default;
    virtual void write(const std::string& data) = 0;
    virtual std::vector<char> read() = 0;
};