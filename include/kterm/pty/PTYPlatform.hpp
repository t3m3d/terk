#pragma once
#include <string>

namespace kterm::pty {

struct PTYHandles {
    int masterFd = -1;
    int childPid = -1;
};

class PTYPlatform {
public:
    static PTYHandles createPTY(const std::string& shellPath, int cols, int rows);
    static void resizePTY(int masterFd, int cols, int rows);
};

}