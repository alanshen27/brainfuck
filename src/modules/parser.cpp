#include "parser.hpp"
#include <stdexcept>
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : m_tokens(tokens), m_index(0) {}

Parser::~Parser() {}

void Parser::parse() {
    m_root.type = NodeType::Program;
    while (currentToken().type != TokenType::_EOF) {
        m_root.children.push_back(parseStatement());
    }
}

Node Parser::rootNode() const {
    return m_root;
}
Node Parser::parseStatement() {
    Node node;
    Token token = currentToken();


    if (token.type == TokenType::GT) {
        // for increment / moving commands, combine multiple commands into a single node with a 'delta' param to decrease the compiled bundle size and RAM usage
        node.type = NodeType::IncrPtr;
        while (peekToken().type == TokenType::GT || peekToken().type == TokenType::LT) {
            if (peekToken().type == TokenType::GT) {
                node.delta++;
            } else {
                node.delta--;
            }
            nextToken();
        }
        if (node.delta < 0) {
            node.delta = -node.delta;
            node.type = NodeType::DecrPtr;
        }
        nextToken();
    } else if (token.type == TokenType::LT) {
        node.type = NodeType::DecrPtr;
        while (peekToken().type == TokenType::GT || peekToken().type == TokenType::LT) {
            if (peekToken().type == TokenType::GT) {
                node.delta--;
            } else {
                node.delta++;
            }
            nextToken();
        }
        if (node.delta < 0) {
            node.delta = -node.delta;
            node.type = NodeType::IncrPtr;
        }
        nextToken();
    } else if (token.type == TokenType::PLUS) {
        node.type = NodeType::IncrByte;
        while (peekToken().type == TokenType::PLUS || peekToken().type == TokenType::MINUS) {
            if (peekToken().type == TokenType::PLUS) {
                node.delta++;
            } else {
                node.delta--;
            }
            nextToken();
        }
        if (node.delta < 0) {
            node.delta = -node.delta;
            node.type = NodeType::DecrByte;
        }
        nextToken();
    } else if (token.type == TokenType::MINUS) {
        node.type = NodeType::DecrByte;
        while (peekToken().type == TokenType::PLUS || peekToken().type == TokenType::MINUS) {
            if (peekToken().type == TokenType::PLUS) {
                node.delta--;
            } else {
                node.delta++;
            }
            nextToken();
        }
        if (node.delta < 0) {
            node.delta = -node.delta;
            node.type = NodeType::IncrByte;
        }
        nextToken();
    } else if (token.type == TokenType::DOT) {
        node.type = NodeType::Output;
        nextToken();
    } else if (token.type == TokenType::COMMA) {
        node.type = NodeType::Input;
        nextToken();
    } else if (token.type == TokenType::LBRACK) {
        node.type = NodeType::Loop;
        nextToken(); // skip '['

        while (currentToken().type != TokenType::RBRACK) {
            // unclosed brackets count as errors
            if (currentToken().type == TokenType::_EOF) {
                throw std::runtime_error("Unclosed '[' at line " + 
                    std::to_string(token.line) + ", column " + std::to_string(token.column));
            }
            node.children.push_back(parseStatement()); // recursively parse the children nodes
        }
        nextToken(); // skip ']'

    } else if (token.type == TokenType::RBRACK) {
        // close brackets without open brackets are obv errors
        throw std::runtime_error("Unexpected ']' at line " + 
            std::to_string(token.line) + ", column " + std::to_string(token.column));
    } else {
        nextToken(); // skip unknown token, edge case, not expected
    }
    return node;
}

Token Parser::currentToken() const {
    return m_tokens[m_index];
}

Token Parser::peekToken() const {
    if (m_index + 1 < m_tokens.size()) {
        return m_tokens[m_index + 1];
    }
    return m_tokens.back(); // return last token, the EOF if no more tokens
}

void Parser::nextToken() {
    if (m_index + 1 < m_tokens.size()) {
        m_index++;
    }
}
