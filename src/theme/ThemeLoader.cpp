#include "kterm/theme/ThemeLoader.hpp"
#include <fstream>
#include <sstream>

using namespace kterm::theme;

Theme ThemeLoader::loadFromFile(const std::string& path) {
    Theme theme;

    std::ifstream file(path);
    if (!file.is_open()) {
        return theme; // return default theme
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string json = buffer.str();

    // --- Minimal stub parser ---
    // You can replace this with real JSON parsing later.
    // For now, we look for simple "fg": "#RRGGBB" patterns.

    auto findValue = [&](const std::string& key) -> std::string {
        size_t pos = json.find(key);
        if (pos == std::string::npos)
            return "";

        size_t start = json.find(":", pos);
        size_t quote1 = json.find("\"", start);
        size_t quote2 = json.find("\"", quote1 + 1);

        if (quote1 == std::string::npos || quote2 == std::string::npos)
            return "";

        return json.substr(quote1 + 1, quote2 - quote1 - 1);
    };

    std::string fgHex = findValue("fg");
    std::string bgHex = findValue("bg");

    if (!fgHex.empty())
        theme.m_scheme.fg = parseColor(fgHex);

    if (!bgHex.empty())
        theme.m_scheme.bg = parseColor(bgHex);

    return theme;
}

uint32_t ThemeLoader::parseColor(const std::string& hex) {
    // Expect "#RRGGBB"
    if (hex.size() != 7 || hex[0] != '#')
        return 0xFFFFFFFF;

    unsigned int r = std::stoul(hex.substr(1, 2), nullptr, 16);
    unsigned int g = std::stoul(hex.substr(3, 2), nullptr, 16);
    unsigned int b = std::stoul(hex.substr(5, 2), nullptr, 16);

    return (0xFF << 24) | (r << 16) | (g << 8) | b;
}