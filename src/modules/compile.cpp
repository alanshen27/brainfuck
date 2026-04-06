#include "compile.hpp"
#include "interpret.hpp"
#include <iostream>

using namespace std;

Compiler::Compiler(const Node& root) : m_root(root) {}

// transpile to C, then compile

Compiler::~Compiler() {}

// @source https://github.com/BaseMax/brainfuck2c/blob/main/brainfuck2c.c
// @note used this transpilation system as a reference (not entirely the same because AST is generated differently)

std::string Compiler::compile() {
    std::string code = "#include <stdio.h>\nint main() {\n";
    code += "\tchar tape[30000] = {0};\n";
    code += " \tchar *ptr = tape;\n";
    for (const Node& node : m_root.children) {
        code += compileNode(node);
    }
    code += "\treturn 0;\n}\n";
    cout << code << endl;
    return code;
}

std::string Compiler::compileNode(const Node& node) {
    switch (node.type) {
    case NodeType::IncrPtr:
        return "\tptr += " + std::to_string(node.delta) + ";\n";
    case NodeType::DecrPtr:
        return "\tptr -= " + std::to_string(node.delta) + ";\n";
    case NodeType::IncrByte:
        return "\t*ptr += " + std::to_string(node.delta) + ";\n";
    case NodeType::DecrByte:
        return "\t*ptr -= " + std::to_string(node.delta) + ";\n";
    case NodeType::Output:
        return "\tputchar(*ptr);\n";
    case NodeType::Input:
        return "\t*ptr = getchar();\n";
    case NodeType::Loop: {
        std::string loopCode = "\twhile (*ptr) {\n";
        for (const Node& child : node.children) {
            loopCode += compileNode(child);
        }
        loopCode += "\t}\n";
        return loopCode;
    }
    default:
        return "";
    }
}