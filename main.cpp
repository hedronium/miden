// Copyright Miden 2018
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "tokenizer.cpp"

using std::endl;
using std::cout;
using std::ifstream;
using std::vector;
using std::string;

struct Model {
    string status;
    string current_token;
    vector<Token*> tokens;
};

vector<Token*> tokenize(string line, Model* model) {
    // take first character and create a new string without the first char
    char c = line[0];
    line = line.substr(1, line.length() - 1);

    if (!c)
        return model;

    if (whitespace(c))
        tokenize(asmc, model)

    if (status.compare("default") == 0) {
        if (alphanumeric(c)) {
            cur_tok += c;
        } else if (c == ':') {
            // Label Declaration
            Token* new_tok = new Token;
            new_tok->name = "LAB";
            new_tok->value = cur_tok;

            tokens.push_back(new_tok);

            cur_tok = "";
        }
    }

    return tokenize(line, model);
}

void debug_token(Token* token) {
    cout << token->name << " = " << token->value << endl;
}

void debug_tokens(vector<Token*> tokens) {
    cout << tokens.size() << " tokens." << endl;
    for (int i = 0; i < tokens.size(); i++)
        debug_token(tokens[i]);
}

int main() {
    // Read characters from assembly file
    // char c;
    ifstream asmc("test.asm");
    // string line;
    // getline(asmc, line);

    // tokenize(line);

    return 0;
}
