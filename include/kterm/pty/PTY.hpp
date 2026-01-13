#pragma once
#include <string>
#include <functional>
#include <vector>

namespace kterm::pty {

class PTY {
public:
    using OutputCallback = std::function<void(const std::vector<char>&)>;

    PTY();
    ~PTY();

    bool spawnShell(const std::string& shellPath = "/bin/bash");
    void setOutputCallback(OutputCallback cb);

    bool writeInput(const std::string& data);
    void resize(int cols, int rows);

private:
    int m_masterFd;
    OutputCallback m_callback;

    void readLoop();
};

} // namespace kterm::pty