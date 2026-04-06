#include "tokenizer.hpp"

Tokenizer::Tokenizer(const std::string& text) : m_text(text) {}

Tokenizer::~Tokenizer() {}

std::vector<Token> Tokenizer::execute() {
    std::vector<Token> tokens;

    // track line and column, justification below
    size_t line = 1;
    size_t column = 1;
    for (size_t i = 0; i < m_text.length(); i++) {
        char c = m_text[i];
        // change a string literal into the `Token` class / type. store the literal for later use (if necessary)
        switch (c) {
            case '>':
                tokens.push_back(Token{TokenType::GT, ">", line, column});
                break;
            case '<':
                tokens.push_back(Token{TokenType::LT, "<", line, column});
                break;
            case '+':
                tokens.push_back(Token{TokenType::PLUS, "+", line, column});
                break;
            case '-':
                tokens.push_back(Token{TokenType::MINUS, "-", line, column});
                break;
            case '.':
                tokens.push_back(Token{TokenType::DOT, ".", line, column});
                break;
            case ',':
                tokens.push_back(Token{TokenType::COMMA, ",", line, column});
                break;
            case '[':
                tokens.push_back(Token{TokenType::LBRACK, "[", line, column});
                break;
            case ']':
                tokens.push_back(Token{TokenType::RBRACK, "]", line, column});
                break;
            default:
                break;
        }
        if (c == '\n') {
            // line number can be stored for error reporting / debugging purposes~ not too necessarily
            line++;
            column = 1;
        } else {
            column++;
        }
    }
    tokens.push_back(Token{TokenType::_EOF, "", line, column}); // add EOF for cleaner parsing (returning last token)
    return tokens;
}