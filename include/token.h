#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    KEYWORD, IDENTIFIER, INTEGER_LITERAL, NUMBER, FLOAT_LITERAL, BOOLEAN_LITERAL,
    STRING_LITERAL, OPERATOR, ASSIGNMENT, SEPARATOR, SEMICOLON, END_OF_FILE
};


struct Token {
    TokenType type;
    std::string value;
};

#endif