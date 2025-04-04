#ifndef IR_EXECUTOR_H
#define IR_EXECUTOR_H

#include "ir_generator.h"
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class IRExecutor {
private:
    std::unordered_map<std::string, int> variables; // Variable storage
    void executeInstruction(const IRInstruction& instr, std::ofstream& execFile);

public:
    void execute(const std::vector<IRInstruction>& instructions);
};

#endif // IR_EXECUTOR_H
