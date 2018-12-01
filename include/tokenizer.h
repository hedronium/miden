// Copyright Miden 2018
#ifndef MIDEN_INCLUDE_TOKENIZER_H_
#define MIDEN_INCLUDE_TOKENIZER_H_

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::cout;
using std::endl;

struct Token {
    string name;
    string value;
};

struct Model {
    string status;
    string currentToken;
    vector<Token> tokens;
};

bool is_numeric(char);

bool is_alphabetic(char);

bool is_alphanumeric(char);

bool is_whitespace(char);

Token new_token(string, string);

Model tokenize(string, Model);

#endif  // MIDEN_INCLUDE_TOKENIZER_H_
