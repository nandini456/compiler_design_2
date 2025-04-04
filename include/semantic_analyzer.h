#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include "parser.h"
#include <unordered_map>
#include <unordered_set>

class SemanticAnalyzer {
private:
    std::unordered_map<std::string, std::string> symbolTable;  // Variable -> Type
    std::unordered_set<std::string> functionTable;  // Tracks function names

    void analyzeNode(ASTNode* node);

public:
    void analyze(ASTNode* root);
};

#endif // SEMANTIC_ANALYZER_H