#include "kterm/pty/PTY.hpp"
#include "kterm/pty/PTYPlatform.hpp"
#include <thread>
#include <unistd.h>
#include <vector>

using namespace kterm::pty;

PTY::PTY() : m_masterFd(-1) {}

PTY::~PTY() {
    if (m_masterFd != -1)
        close(m_masterFd);
}

bool PTY::spawnShell(const std::string& shellPath) {
    auto handles = PTYPlatform::createPTY(shellPath, 80, 24);
    if (handles.masterFd < 0)
        return false;

    m_masterFd = handles.masterFd;

    std::thread reader(&PTY::readLoop, this);
    reader.detach();

    return true;
}

void PTY::setOutputCallback(OutputCallback cb) {
    m_callback = cb;
}

bool PTY::writeInput(const std::string& data) {
    if (m_masterFd < 0)
        return false;

    ssize_t written = write(m_masterFd, data.data(), data.size());
    return written == (ssize_t)data.size();
}

void PTY::resize(int cols, int rows) {
    if (m_masterFd >= 0)
        PTYPlatform::resizePTY(m_masterFd, cols, rows);
}

void PTY::readLoop() {
    std::vector<char> buffer(4096);

    while (true) {
        ssize_t n = read(m_masterFd, buffer.data(), buffer.size());
        if (n <= 0)
            break;

        if (m_callback)
            m_callback(std::vector<char>(buffer.begin(), buffer.begin() + n));
    }
}