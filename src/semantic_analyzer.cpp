#include "semantic_analyzer.h"
#include <iostream>

void SemanticAnalyzer::analyzeNode(ASTNode* node) {
    if (!node) return;

    // ✅ Ignore keywords (e.g., START, FUNCTION, IF, RETURN)
    if (node->type == "KEYWORD") {
        return;
    }

    // ✅ Ignore operators (e.g., ==, *, -, (, ))
    if (node->type == "OPERATOR" || node->type == "PUNCTUATION") {
        return;
    }

    // ✅ Ignore numbers (they are literals, not variables)
    if (node->type == "NUMBER") {
        return;
    }

    // ✅ Ignore function declarations (track them separately)
    if (node->type == "FunctionDeclaration") {
        functionTable.insert(node->value);
        return;
    }

    // ✅ Variable Assignment (e.g., `x = 5`)
    if (node->type == "Expression" && node->value == "=") {
        std::string varName = node->children[0]->value;  // Variable name
        std::string varType = node->children[1]->type;   // Type of assigned value

        symbolTable[varName] = varType;  // ✅ Store in symbol table
    }

    // ❌ Check for Undeclared Variables (ignore if it's a function call)
    if (node->type == "Expression" && symbolTable.find(node->value) == symbolTable.end() && functionTable.find(node->value) == functionTable.end()) {
        std::cout << "Semantic Error: Variable '" << node->value << "' used before declaration." << std::endl;
    }

    // 🔄 **Recursively Analyze Child Nodes**
    for (auto& child : node->children) {
        analyzeNode(child.get());  // Convert unique_ptr<ASTNode> to ASTNode*
    }
}

void SemanticAnalyzer::analyze(ASTNode* root) {
    std::cout << "Starting Semantic Analysis..." << std::endl;
    analyzeNode(root);
}