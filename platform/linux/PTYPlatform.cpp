#include "kterm/pty/PTYPlatform.hpp"
#include <pty.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

using namespace kterm::pty;

PTYHandles PTYPlatform::createPTY(const std::string& shellPath, int cols, int rows) {
    PTYHandles handles;

    struct winsize ws;
    ws.ws_col = cols;
    ws.ws_row = rows;
    ws.ws_xpixel = 0;
    ws.ws_ypixel = 0;

    int masterFd;
    int childPid = forkpty(&masterFd, nullptr, nullptr, &ws);

    if (childPid < 0)
        return handles;

    if (childPid == 0) {
        execl(shellPath.c_str(), shellPath.c_str(), nullptr);
        _exit(1);
    }

    handles.masterFd = masterFd;
    handles.childPid = childPid;
    return handles;
}

void PTYPlatform::resizePTY(int masterFd, int cols, int rows) {
    struct winsize ws;
    ws.ws_col = cols;
    ws.ws_row = rows;
    ws.ws_xpixel = 0;
    ws.ws_ypixel = 0;

    ioctl(masterFd, TIOCSWINSZ, &ws);
}