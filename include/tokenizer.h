// Copyright Miden 2018
#ifndef MIDEN_INCLUDES_TOKENIZER_H_
#define MIDEN_INCLUDES_TOKENIZER_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Token {
    string name;
    string value;
};

struct Model {
    string status;
    string currentToken;
    vector<Token*> tokens;
};

bool is_numeric(char);

bool is_alphabetic(char);

bool is_alphanumeric(char);

bool is_whitespace(char);

Model tokenize(string, Model);

#endif  // MIDEN_INCLUDES_TOKENIZER_H_
