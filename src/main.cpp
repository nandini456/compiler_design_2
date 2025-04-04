#include "lexer.h"
#include <iostream>
#include <fstream>  // Include for file handling
#include <sstream>  // For stringstream
using namespace std;

int main() {
    // Open the input file
    ifstream inputFile("tests/input.txt");
    if (!inputFile) {
        cerr << "Error: Could not open tests/input.txt for reading!" << endl;
        return 1;
    }

    // Read the entire content of the file into a string
    stringstream buffer;
    buffer << inputFile.rdbuf();
    string input = buffer.str();
    inputFile.close();

    Lexer lexer(input);
    auto tokens = lexer.tokenize();

    // Open file for writing tokens
    ofstream tokensFile("tests/tokens.txt");
    if (!tokensFile) {
        cerr << "Error: Could not open tests/tokens.txt for writing!" << endl;
        return 1;
    }

    // Write tokens to file
    for (auto& token : tokens) {
        tokensFile << token.value << " [" << static_cast<int>(token.type) << "]\n";
    }

    cout << "Tokenization completed! Tokens saved to tests/tokens.txt" << endl;
    tokensFile.close();
    return 0;
}
