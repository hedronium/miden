// Copyright Miden 2018
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../include/tokenizer.h"

using std::endl;
using std::cout;
using std::ifstream;
using std::vector;
using std::string;

void debug_token(Token* token) {
    cout << token->name << " = " << token->value << endl;
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

    // model = tokenize("li $s0, 0\n", model);
    // model = tokenize("li $a0, 2\n", model);
    // model = tokenize("li $a1, 3\n", model);

    while (getline(asmc, line)) {
        model = tokenize(line + " ", model);
    }

    debug_tokens(model);

    return 0;
}
