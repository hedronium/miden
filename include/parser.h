// Copyright Miden 2018
#ifndef MIDEN_INCLUDE_PARSER_H_
#define MIDEN_INCLUDE_PARSER_H_

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../include/tokenizer.h"
#include "../include/maybe.h"

using std::cout;
using std::endl;
using std::ostringstream;
using std::to_string;
using std::stoi;
using std::reverse;

string parse(int, Model);
string parse(Model);
string fixed_size_binary(string, int);
string decimal_to_binary(string);
bool token_exists(int, Model);

#endif  // MIDEN_INCLUDE_PARSER_H_
