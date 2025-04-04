// #include "lexer.h"
// #include <cctype>
// #include <iostream>

// Lexer::Lexer(const string& input) : input(input), pos(0) {
//     currentChar = input.empty() ? '\0' : input[0];

//     // Define keywords
//     keywords = {
//         {"START", TokenType::KEYWORD}, {"END", TokenType::KEYWORD},{"DO",TokenType::KEYWORD},
//         {"ARRAY", TokenType::KEYWORD}, {"STRUCT", TokenType::KEYWORD},
//         {"IF", TokenType::KEYWORD}, {"ELSE", TokenType::KEYWORD},
//         {"WHILE", TokenType::KEYWORD}, {"FOR", TokenType::KEYWORD},
//         {"FUNCTION", TokenType::KEYWORD}, {"RETURN", TokenType::KEYWORD},
//         {"PRINT", TokenType::KEYWORD}, {"TRUE", TokenType::BOOLEAN_LITERAL}, 
//         {"FALSE", TokenType::BOOLEAN_LITERAL},
//         {"AND", TokenType::KEYWORD}, {"OR", TokenType::KEYWORD}, {"NOT", TokenType::KEYWORD}
//     };
// }

// void Lexer::advance() {
//     pos++;
//     currentChar = (pos < input.length()) ? input[pos] : '\0';
// }

// void Lexer::skipWhitespace() {
//     while (isspace(currentChar)) {
//         advance();
//     }
// }

// Token Lexer::getNumber() {
//     string num;
//     bool hasDecimal = false;

//     while (isdigit(currentChar) || currentChar == '.') {
//         if (currentChar == '.') {
//             if (hasDecimal) break;
//             hasDecimal = true;
//         }
//         num += currentChar;
//         advance();
//     }

//     return {hasDecimal ? TokenType::FLOAT_LITERAL : TokenType::INTEGER_LITERAL, num};
// }

// Token Lexer::getString() {
//     string str;
//     advance(); // Skip opening quote

//     while (currentChar != '"' && currentChar != '\0') {
//         str += currentChar;
//         advance();
//     }

//     if (currentChar == '"') {
//         advance(); // Skip closing quote
//     } else {
//         cerr << "Error: Unterminated string literal!" << endl;
//     }

//     return {TokenType::STRING, str};
// }

// Token Lexer::getIdentifier() {
//     string id;

//     while (isalnum(currentChar) || currentChar == '_') {
//         id += currentChar;
//         advance();
//     }

//     if (keywords.count(id)) {
//         return {keywords[id], id}; // Fixed: return directly from keyword map
//     }

//     return {TokenType::IDENTIFIER, id};
// }

// Token Lexer::getOperator() {
//     string op(1, currentChar);

//     if (currentChar == '=') {  
//         advance();
//         if (currentChar == '=') {  // Check for '=='
//             op += currentChar;
//             advance();
//             return {TokenType::OPERATOR, op};  // "=="
//         }
//         return {TokenType::ASSIGNMENT, "="};  // Single '=' is assignment
//     }

//     if (currentChar == '!' || currentChar == '<' || currentChar == '>') {
//         advance();
//         if (currentChar == '=') {  
//             op += currentChar;
//             advance();
//         }
//     } 
//     else {
//         advance();
//     }

//     return {TokenType::OPERATOR, op};
// }



// Token Lexer::getSeparator() {
//     string separator(1, currentChar);
//     advance(); // Move to next character

//     return {TokenType::SEPARATOR, separator};
// }

// vector<Token> Lexer::tokenize() {
//     vector<Token> tokens;
//     while (currentChar != '\0') {
//         if (isspace(currentChar)) {
//             skipWhitespace();
//             continue;
//         }

//         if (isdigit(currentChar)) {
//             tokens.push_back(getNumber());
//             continue;
//         }

//         if (isalpha(currentChar)) {
//             tokens.push_back(getIdentifier());
//             continue;
//         }

//         if (currentChar == '"') {
//             tokens.push_back(getString());
//             continue;
//         }
//         // Recognize separators
//         if (currentChar == ',' || currentChar == ';' || currentChar == '(' || currentChar == ')' ||
//             currentChar == '{' || currentChar == '}' || currentChar == '[' || currentChar == ']') {
//             tokens.push_back(getSeparator());
//             continue;
//         }

//         if (ispunct(currentChar)) {
//             tokens.push_back(getOperator());
//             continue;
//         }

//         advance();
//     }

//     tokens.push_back({TokenType::END_OF_FILE, "EOF"});
//     return tokens;
// }
#include "lexer.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(const string& input): input(input), pos(0) {
    currentChar = input.empty() ? '\0' : input[0];
    keywords = {
        {"START", TokenType::KEYWORD}, {"END", TokenType::KEYWORD},
        {"VAR", TokenType::KEYWORD}, {"IF", TokenType::KEYWORD},
        {"ELSE", TokenType::KEYWORD}, {"WHILE", TokenType::KEYWORD},
        {"FUNCTION", TokenType::KEYWORD}, {"RETURN", TokenType::KEYWORD},
        {"PRINT", TokenType::KEYWORD}, {"TRUE", TokenType::BOOLEAN_LITERAL},
        {"FALSE", TokenType::BOOLEAN_LITERAL}
    };
}

void Lexer::advance() {
    pos++;
    currentChar = (pos < input.size()) ? input[pos] : '\0';
}

void Lexer::skipWhitespace() {
    while (isspace(currentChar))
        advance();
}

Token Lexer::getNumber() {
    string number;
    bool hasDecimal = false;

    while (isdigit(currentChar) || currentChar == '.') {
        if (currentChar == '.') {
            if (hasDecimal) break;
            hasDecimal = true;
        }
        number += currentChar;
        advance();
    }

    return {hasDecimal ? TokenType::FLOAT_LITERAL : TokenType::INTEGER_LITERAL, number};
}

Token Lexer::getIdentifierOrKeyword() {
    string id;

    while (isalnum(currentChar) || currentChar == '_') {
        id += currentChar;
        advance();
    }

    if (keywords.count(id)) {
        return {keywords[id], id};
    }

    return {TokenType::IDENTIFIER, id};
}

Token Lexer::getString() {
    string str;
    advance(); // skip opening quote

    while (currentChar != '"' && currentChar != '\0') {
        str += currentChar;
        advance();
    }
    advance(); // skip closing quote
    return {TokenType::STRING_LITERAL, str};
}

Token Lexer::getOperator() {
    string op(1, currentChar);
    advance();

    if ((op == "=" || op == "!" || op == "<" || op == ">") && currentChar == '=') {
        op += currentChar;
        advance();
    }

    return {(op == "=") ? TokenType::ASSIGNMENT : TokenType::OPERATOR, op};
}

Token Lexer::getSeparator() {
    string sep(1, currentChar);
    advance();
    return {TokenType::SEPARATOR, sep};
}

vector<Token> Lexer::tokenize() {
    vector<Token> tokens;

    while (currentChar != '\0') {
        if (isspace(currentChar)) {
            skipWhitespace();
            continue;
        }

        if (isdigit(currentChar)) {
            tokens.push_back(getNumber());
            continue;
        }

        if (isalpha(currentChar) || currentChar == '_') {
            tokens.push_back(getIdentifierOrKeyword());
            continue;
        }

        if (currentChar == '"') {
            tokens.push_back(getString());
            continue;
        }

        if (ispunct(currentChar)) {
            if (string(";,(){}[]").find(currentChar) != string::npos) {
                tokens.push_back(getSeparator());
            } else {
                tokens.push_back(getOperator());
            }
            continue;
        }
    }

    tokens.push_back({TokenType::END_OF_FILE, "EOF"});
    return tokens;
}