#pragma once
#include <cstdint>

namespace kterm::renderer {

struct Cell {
    char ch = ' ';
    uint32_t fg = 0xFFFFFFFF;
    uint32_t bg = 0x00000000;
};

}