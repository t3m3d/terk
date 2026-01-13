#pragma once
#include <string>
#include <unordered_map>

namespace kterm::theme {

struct ColorScheme {
    uint32_t fg;
    uint32_t bg;
    std::unordered_map<int, uint32_t> palette;
};

class Theme {
public:
    bool loadFromFile(const std::string& path);
    const ColorScheme& scheme() const;

private:
    ColorScheme m_scheme;
};

}