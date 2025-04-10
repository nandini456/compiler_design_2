// #include "parser.h"
// #include <iostream>

// Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)), currentPos(0) {
//     stateStack.push(0);  // Initial state
// }

// std::unique_ptr<ASTNode> Parser::parse() {
//     while (true) {
//         Token currentToken = tokens[currentPos];
//         int state = stateStack.top();
        
//         ParserAction action = getAction(state, currentToken.type);
        
//         switch (action.type) {
//             case ParserActionType::SHIFT:
//                 shift(action.value);
//                 break;
//             case ParserActionType::REDUCE:
//                 reduce(action.value);
//                 break;
//             case ParserActionType::ACCEPT:
//                 return std::move(astStack.top());
//             case ParserActionType::ERROR:
//                 std::cerr << "Syntax Error at token: " << currentToken.value << std::endl;
//                 return nullptr;
//         }
//     }
// }
// void Parser::shift(int state) {
//     stateStack.push(state);  // Move to new state
//     astStack.push(std::make_unique<ASTNode>(tokens[currentPos]));  // Push AST node for token
//     currentPos++;  // Consume the token
// }

// // Reduce function: Pops nodes based on a rule, creates a new AST node, and pushes back
// void Parser::reduce(int rule) {
//     int popCount = grammarRules[rule].rhsSize;  // Number of items to pop
//     std::vector<std::unique_ptr<ASTNode>> children;

//     // Pop RHS nodes and store them as children
//     for (int i = 0; i < popCount; i++) {
//         children.insert(children.begin(), std::move(astStack.top()));
//         astStack.pop();
//         stateStack.pop();  // Pop state as well
//     }

//     // Create AST node for LHS
//     auto newNode = std::make_unique<ASTNode>(grammarRules[rule].lhs);
//     newNode->children = std::move(children);

//     // Push new AST node back
//     astStack.push(std::move(newNode));

//     // Get new state from parsing table
//     int newState = gotoTable[stateStack.top()][grammarRules[rule].lhs];
//     stateStack.push(newState);
// }

// // Parsing Table Lookup: Returns action (SHIFT, REDUCE, ACCEPT, ERROR)
// ParserAction Parser::getAction(int state, TokenType token) {
//     if (parsingTable[state].find(token) != parsingTable[state].end()) {
//         return parsingTable[state][token];  // Return action if exists
//     }
//     return { ParserActionType::ERROR, -1 };  // Default to ERROR
// }

#include "parser.h"
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), currentPos(0) {
    stateStack.push(0);

    grammarRules = {
        { NonTerminal::STATEMENT, 3 } // STATEMENT -> IDENTIFIER ASSIGNMENT NUMBER
    };

    parsingTable = {
        { 0, { { TokenType::IDENTIFIER, { ParserActionType::SHIFT, 1 } } } },
        { 1, { { TokenType::ASSIGNMENT, { ParserActionType::SHIFT, 2 } } } },
        { 2, { { TokenType::NUMBER, { ParserActionType::SHIFT, 3 } } } },
        { 3, { { TokenType::SEMICOLON, { ParserActionType::REDUCE, 0 } } } },
        { 4, { { TokenType::END_OF_FILE, { ParserActionType::ACCEPT, 0 } } } }
    };

    gotoTable = {
        { 0, { { NonTerminal::STATEMENT, 4 } } }
    };
}


std::unique_ptr<ASTNode> Parser::parse() {
    while (true) {
        Token currentToken = tokens[currentPos];
        int state = stateStack.top();

        ParserAction action = getAction(state, currentToken.type);

        switch (action.type) {
            case ParserActionType::SHIFT:
                shift(action.value);
                break;
            case ParserActionType::REDUCE:
                reduce(action.value);
                break;
            case ParserActionType::ACCEPT:
                return std::move(astStack.top());
            case ParserActionType::ERROR:
                std::cerr << "Syntax Error at token: " << currentToken.value << std::endl;
                return nullptr;
        }
    }
}

void Parser::shift(int state) {
    stateStack.push(state);
    astStack.push(std::make_unique<ASTNode>(tokens[currentPos]));
    currentPos++;
}

void Parser::reduce(int rule) {
    int popCount = grammarRules[rule].rhsSize;
    std::vector<std::unique_ptr<ASTNode>> children;

    for (int i = 0; i < popCount; ++i) {
        children.insert(children.begin(), std::move(astStack.top()));
        astStack.pop();
        stateStack.pop();
    }

    auto newNode = std::make_unique<ASTNode>(grammarRules[rule].lhs);
    newNode->children = std::move(children);

    astStack.push(std::move(newNode));

    int newState = gotoTable[stateStack.top()][grammarRules[rule].lhs];
    stateStack.push(newState);
}

ParserAction Parser::getAction(int state, TokenType token) {
    if (parsingTable[state].find(token) != parsingTable[state].end()) {
        return parsingTable[state][token];
    }
    return { ParserActionType::ERROR, -1 };
}
