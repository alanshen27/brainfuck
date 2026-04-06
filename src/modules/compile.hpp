#pragma once

#include <string>
#include "parser.hpp"

class Compiler {
public:
    Compiler(const Node& root);
    ~Compiler();

    std::string compile();

private:
    Node m_root;
    std::string compileNode(const Node& node);
};
