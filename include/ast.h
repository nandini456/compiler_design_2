// #ifndef AST_H
// #define AST_H

// #include <string>
// #include <vector>
// #include <memory>

// // AST Node structure
// class ASTNode {
// public:
//     std::string type;  // Node type (e.g., "Assignment", "Expression", "IfStatement")
//     std::string value; // Value (e.g., variable name, operator, number)
//     std::vector<std::unique_ptr<ASTNode>> children; // Child nodes

//     // Constructor
//     ASTNode(std::string type, std::string value) : type(type), value(value) {}

//     // Add child node
//     void addChild(std::unique_ptr<ASTNode> child) {
//         children.push_back(std::move(child));
//     }
// };

// #endif // AST_H
#ifndef AST_H
#define AST_H

#include <vector>
#include <memory>
#include <string>

enum class NonTerminal {
    STATEMENT,
    EXPRESSION
    // add more as needed
};

class ASTNode {
public:
    NonTerminal type;
    std::string value;
    std::vector<std::unique_ptr<ASTNode>> children;

    ASTNode(Token token) : value(token.value) {}
    ASTNode(NonTerminal t) : type(t) {}
};

#endif
