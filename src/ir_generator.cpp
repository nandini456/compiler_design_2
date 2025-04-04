#include "ir_generator.h"
#include <iostream>

using namespace std;

int tempVarCount = 0; // Counter for temporary variables

// Helper function to generate a new temporary variable
string newTempVar() {
    return "t" + to_string(tempVarCount++);
}

// Function to map AST operator types to TAC instructions
string getTACOperator(const string& op) {
    if (op == "+") return "ADD";
    if (op == "-") return "SUB";
    if (op == "*") return "MUL";
    if (op == "/") return "DIV";
    return "UNKNOWN";
}

// Recursive function to generate IR from AST
string IRGenerator::generateTAC(ASTNode* node, vector<IRInstruction>& instructions) {
    if (!node) return "";

    // Handle numbers and variables directly
    if (node->type == "Number" || node->type == "Variable") {
        return node->value;
    }

    // Handle binary operations (+, -, *, /)
    if (node->type == "Operator") {
        string leftOperand = generateTAC(node->children[0].get(), instructions);
        string rightOperand = generateTAC(node->children[1].get(), instructions);
        string result = newTempVar();  // Create temp variable

        string tacOp = getTACOperator(node->value); // Convert operator to TAC instruction
        instructions.push_back(IRInstruction{tacOp, result + ", " + leftOperand + ", " + rightOperand});
        return result;
    }

    // Handle assignments (x = expr)
    if (node->type == "Assignment") {
        string varName = node->children[0]->value; // Left-hand side variable
        string exprResult = generateTAC(node->children[1].get(), instructions); // Compute right-hand side

        instructions.push_back(IRInstruction{"MOV", varName + ", " + exprResult});
        return varName;
    }

    // Handle PRINT statements
    if (node->type == "PrintStatement") {
        string printValue = generateTAC(node->children[0].get(), instructions);
        instructions.push_back(IRInstruction{"PRINT", printValue});
        return "";
    }

    // Recursively process all child nodes
    for (const auto& child : node->children) {
        generateTAC(child.get(), instructions);
    }

    return "";
}

// Main function to generate IR
vector<IRInstruction> IRGenerator::generateIR(ASTNode* root) {
    vector<IRInstruction> instructions;
    if (!root) {
        cout << "IR Generator: No AST root found!\n";
        return instructions;
    }

    cout << "Generating TAC IR...\n";
    generateTAC(root, instructions);
    
    // Debugging: Print IR instructions
    for (const auto& instr : instructions) {
        cout << instr.opcode << " " << instr.operand << endl;
    }

    return instructions;
}
