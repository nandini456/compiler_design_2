#include "ir_executor.h"
#include <sstream>
#include <fstream>

using namespace std;

// Function to convert a string to an integer
int toInt(const string& str) {
    stringstream ss(str);
    int value;
    ss >> value;
    return value;
}

// Execute a single IR instruction
void IRExecutor::executeInstruction(const IRInstruction& instr, ofstream& execFile) {
    string opcode = instr.opcode;
    string operand = instr.operand;
    vector<string> parts;
    stringstream ss(operand);
    string part;

    // Split the operand by commas
    while (getline(ss, part, ',')) {
        parts.push_back(part);
    }

    // Trim whitespace from parts
    for (auto& p : parts) {
        p.erase(0, p.find_first_not_of(" "));
        p.erase(p.find_last_not_of(" ") + 1);
    }

    // Handle Arithmetic Operations (ADD, SUB, MUL, DIV)
    if (opcode == "ADD" || opcode == "SUB" || opcode == "MUL" || opcode == "DIV") {
        string resultVar = parts[0];
        string left = parts[1];
        string right = parts[2];

        // Get values from variables or parse integers directly
        int leftVal = (variables.find(left) != variables.end()) ? variables[left] : toInt(left);
        int rightVal = (variables.find(right) != variables.end()) ? variables[right] : toInt(right);

        if (opcode == "ADD") variables[resultVar] = leftVal + rightVal;
        if (opcode == "SUB") variables[resultVar] = leftVal - rightVal;
        if (opcode == "MUL") variables[resultVar] = leftVal * rightVal;
        if (opcode == "DIV") variables[resultVar] = rightVal != 0 ? leftVal / rightVal : 0;
    }
    // Handle MOV (Assignment)
    else if (opcode == "MOV") {
        string varName = parts[0];
        string value = parts[1];

        // Assign value to variable
        variables[varName] = (variables.find(value) != variables.end()) ? variables[value] : toInt(value);
    }
    // Handle PRINT
    else if (opcode == "PRINT") {
        string varName = parts[0];
        if (variables.find(varName) != variables.end()) {
            cout << variables[varName] << endl;  // Print to console
            execFile << variables[varName] << endl; // Save to file
        } else {
            cout << "Error: Undefined variable " << varName << endl;
            execFile << "Error: Undefined variable " << varName << endl;
        }
    }
}

// Execute all IR instructions and save output to file
void IRExecutor::execute(const vector<IRInstruction>& instructions) {
    ofstream execFile("./tests/ir_execution.txt");
    if (!execFile) {
        cerr << "Error: Could not open IR execution output file!" << endl;
        return;
    }

    for (const auto& instr : instructions) {
        executeInstruction(instr, execFile);
    }

    execFile.close();
}
