// #ifndef PARSER_H
// #define PARSER_H

// #include <stack>
// #include <map>
// #include <vector>
// #include <memory>
// #include "token.h"
// #include "ast.h"

// // Parser action types
// enum class ParserActionType { SHIFT, REDUCE, ACCEPT, ERROR };

// // Action struct: Defines an action in the parsing table
// struct ParserAction {
//     ParserActionType type;
//     int value;  // State number (for shift) or rule number (for reduce)
// };

// class Parser {
// private:
//     std::vector<Token> tokens;  // Token stream
//     int currentPos = 0;  // Token position
//     std::stack<int> stateStack;  // Stack for states
//     std::stack<std::unique_ptr<ASTNode>> astStack;  // AST node stack

//     // Parsing table (state → token → action)
//     std::map<int, std::map<TokenType, ParserAction>> parsingTable;

//     // Goto table (state → nonterminal → new state)
//     std::map<int, std::map<NonTerminal, int>> gotoTable;

// public:
//     Parser(const std::vector<Token>& tokens) : tokens(tokens) {}

//     void shift(int state);
//     void reduce(int rule);
//     ParserAction getAction(int state, TokenType token);
// };

// #endif

#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include <map>
#include <vector>
#include <memory>
#include "token.h"
#include "ast.h"

enum class ParserActionType { SHIFT, REDUCE, ACCEPT, ERROR };

struct ParserAction {
    ParserActionType type;
    int value;
};

struct GrammarRule {
    NonTerminal lhs;
    int rhsSize;
};

class Parser {
private:
    std::vector<Token> tokens;
    int currentPos;
    std::stack<int> stateStack;
    std::stack<std::unique_ptr<ASTNode>> astStack;

    std::map<int, std::map<TokenType, ParserAction>> parsingTable;
    std::map<int, std::map<NonTerminal, int>> gotoTable;
    std::vector<GrammarRule> grammarRules;

public:
    Parser(const std::vector<Token>& tokens);
    std::unique_ptr<ASTNode> parse();
    void shift(int state);
    void reduce(int rule);
    ParserAction getAction(int state, TokenType token);
};

#endif
