// Copyright Miden 2018
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../include/tokenizer.h"
#include "../include/parser.h"

using std::endl;
using std::cout;
using std::cin;
using std::ifstream;
using std::vector;
using std::string;
using std::ofstream;
using std::ios;

void debug_token(Token token) {
    cout << token.name << " = " << token.value << endl;
}

void debug_tokens(Model model) {
    cout << model.tokens.size() << " tokens." << endl;
    for (int i = 0; i < model.tokens.size(); i++)
        debug_token(model.tokens[i]);
}

int main() {
    // gather 1 line of assembly code
    ifstream asmc("input.asm");
    string line;
    // getline(asmc, line);

    // setup model
    Model model;
    model.status = "default";
    model.currentToken = "";
    model.currentInstructionAddress = 0;

    string input_file_name;
    cout << "Name of the input file: " << endl;
    cin >> input_file_name;

    string output_file_name;
    cout << "Name of the output file: " << endl;
    cin >> output_file_name;

    // tokenize
    while (getline(asmc, line)) {
        model = tokenize(line + " ", model);
    }

    // debug_tokens(model);

    ofstream output(output_file_name);
    output << parse(model) << endl;

    return 0;
}
