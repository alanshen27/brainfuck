#pragma once

#include <vector>
#include "parser.hpp"

class Interpreter {
public:
    Interpreter(const Node& root, size_t memorySize = 30000);
    ~Interpreter();

    void execute();

private:
    Node m_root;
    std::vector<unsigned char> m_memory;
    size_t m_ptr = 0;

    void executeNode(const Node& node);
    void executeLoop(const Node& node);
};
