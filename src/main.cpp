// Copyright Miden 2018
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../include/tokenizer.h"
#include "../include/parser.h"

using std::endl;
using std::cout;
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

    // model = tokenize("li $s0, 0\n", model);
    // model = tokenize("addi $s0, $t0, 1\n", model);
    // model = tokenize("lw $s0, 4($sp)\n", model);

    while (getline(asmc, line)) {
        model = tokenize(line + " ", model);
    }

    // debug_tokens(model);

    // cout << parse(0, model) << endl;

    return 0;
}
