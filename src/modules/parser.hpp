#pragma once

#include <vector>
#include <string>
#include "tokenizer.hpp"

enum class NodeType : unsigned char {
    Program,
    IncrPtr,
    DecrPtr,
    IncrByte,
    DecrByte,
    Output,
    Input,
    Loop,
};

inline std::string nodeTypeToString(NodeType type) {
    switch (type) {
        case NodeType::Program: return "Program";
        case NodeType::IncrPtr: return "IncrPtr";
        case NodeType::DecrPtr: return "DecrPtr";
        case NodeType::IncrByte: return "IncrByte";
        case NodeType::DecrByte: return "DecrByte";
        case NodeType::Output: return "Output";
        case NodeType::Input: return "Input";
        case NodeType::Loop: return "Loop";
    }
    return "Unknown";
}

struct Node {
    NodeType type;
    std::vector<Node> children;
    int delta = 1;
    std::string format(const std::string& prefix = "" /* for children nodes adding \t */) const {
        std::string result = prefix;
        result += nodeTypeToString(type); // stringify node
        if (delta >=0) {
            result += " (delta: " + std::to_string(delta) + ")";
        }
        for (size_t i = 0; i < children.size(); i++) {
            result +='\n' + children[i].format(prefix + ("\t")); // allows for '\t' to stack for nested systems. prefix accumulates more '\t's
        }
        return result;
    };
};

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    ~Parser();

    void parse();
    Node parseStatement();
    Node rootNode() const;
private:
    std::vector<Token> m_tokens;
    size_t m_index = 0;
    Node m_root;

    Token currentToken() const;
    Token peekToken() const;
    void nextToken();
};