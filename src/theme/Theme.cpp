#include "kterm/theme/Theme.hpp"
#include <fstream>

using namespace kterm::theme;

bool Theme::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    // Parse JSON (stubbed for now)
    m_scheme.fg = 0xFFFFFFFF;
    m_scheme.bg = 0x00000000;
    return true;
}

const ColorScheme& Theme::scheme() const {
    return m_scheme;
}