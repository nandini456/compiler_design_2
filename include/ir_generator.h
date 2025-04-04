#ifndef IR_GENERATOR_H
#define IR_GENERATOR_H

#include "parser.h"
#include <vector>
#include <string>

struct IRInstruction {
    std::string opcode;
    std::string operand;
};

class IRGenerator {
public:
    std::vector<IRInstruction> generateIR(ASTNode* ast);
private:
    std::string generateTAC(ASTNode* node, std::vector<IRInstruction>& instructions);
};

#endif // IR_GENERATOR_H
