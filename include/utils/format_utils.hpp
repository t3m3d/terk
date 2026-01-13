#pragma once
#include <string>

namespace kterm::utils {

std::string padLeft(const std::string& text, size_t width, char fill = ' ');
std::string padRight(const std::string& text, size_t width, char fill = ' ');

}