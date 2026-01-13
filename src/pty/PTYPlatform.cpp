#include "kterm/pty/PTYPlatform.hpp"

#if defined(__linux__)
#include "../../platform/linux/PTYPlatform.cpp"
#elif defined(_WIN32)
#include "../../platform/windows/PTYPlatform.cpp"
#else
#error "Unsupported platform"
#endif