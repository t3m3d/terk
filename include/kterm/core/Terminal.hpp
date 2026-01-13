#pragma once
#include <string>
#include <vector>
#include <functional>
#include "kterm/renderer/Grid.hpp"
#include "kterm/parser/AnsiParser.hpp"

namespace kterm::core {

class Terminal {
public:
    using RenderCallback = std::function<void()>;

    Terminal(int cols = 80, int rows = 24);
    ~Terminal() = default;

    void setRenderCallback(RenderCallback cb);

    void onPTYOutput(const std::vector<char>& data);
    void writeToPTY(const std::string& input);

    void resize(int cols, int rows);

    renderer::Grid& grid();
    const renderer::Grid& grid() const;

private:
    renderer::Grid m_grid;
    parser::AnsiParser m_parser;

    RenderCallback m_renderCallback;

    void applyText(const std::string& text);
    void applyEscape(const parser::EscapeSequence& seq);
};

}