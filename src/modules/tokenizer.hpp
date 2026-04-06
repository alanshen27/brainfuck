#pragma once

#include <string>
#include <vector>

enum class TokenType : unsigned char {
    GT,
    LT,
    PLUS,
    MINUS,
    DOT,
    COMMA,
    LBRACK,
    RBRACK,
    _EOF,
};

struct Token {
    TokenType type;
    std::string literal;
    size_t line;
    size_t column;
    std::string format() const {
        return "Token(" + std::to_string(static_cast<int>(type)) + ", literal: " + literal + ", line: " + std::to_string(line) + ", column: " + std::to_string(column) + ")";
    };
};

class Tokenizer {
public:
    Tokenizer(const std::string& text);
    ~Tokenizer();

    std::vector<Token> execute();
private:
    std::string m_text;
};