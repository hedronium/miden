// Copyright Miden 2018
#ifndef MIDEN_INCLUDE_MODEL_H_
#define MIDEN_INCLUDE_MODEL_H_

#include <string>
#include <vector>
#include "./token.h"
#include "./label.h"

using std::string;
using std::vector;

struct Model {
    string status;
    string currentToken;
    vector<Token> tokens;
    vector<Label> labels;
    int currentInstructionAddress;
};

#endif  // MIDEN_INCLUDE_MODEL_H_
