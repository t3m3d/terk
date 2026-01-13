#include "kterm/pty/PTYPlatform.hpp"

using namespace kterm::pty;

PTYHandles PTYPlatform::createPTY(const std::string&, int, int) {
    return {};
}

void PTYPlatform::resizePTY(int, int, int) {}