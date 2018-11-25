// Copyright Miden 2018
#include <iostream>
#include "includes/tokenizer.h"

using std::cout;
using std::endl;

bool is_numeric(char c) {
    if (c >= 48 && c <= 57)
        return true;
    return false;
}

bool is_alphabetic(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return true;
    return false;
}

bool is_alphanumeric(char c) {
    return is_alphabetic(c) || is_numeric(c);
}

bool is_whitespace(char c) {
    if (c == 32 || c == 9 || c == 10)
        return true;
    return false;
}

Token* new_token(string name, string value) {
    Token* token = new Token;
    token->name = name;
    token->value = value;
    return token;
}

Model tokenize(string line, Model model) {
    int last_character = 0;

    if (line.length() == 0)
        return model;
    else if (line.length() == 1)
        last_character = 1;

    /* store the first character and create a new string
       excluding the first char */
    char c = line[0];
    line = line.substr(1, line.length() - 1);

    if (model.status.compare("default") == 0) {
         // default

        if (is_alphanumeric(c)) {
            model.currentToken += c;
        } else if (c == ':') {
            // Label Declaration
            model.tokens.push_back(
                new_token("LBL", model.currentToken));

            model.currentToken = "";
        } else if (is_whitespace(c)) {
            if (model.currentToken.length() > 0) {
                // Keyword
                model.tokens.push_back(
                    new_token("KWD", model.currentToken));

                model.currentToken = "";
            }
        } else if (c == '$') {
            model.status = "register";
        }

        if (last_character && model.currentToken.length() > 0) {
            // Keyword
            model.tokens.push_back(
                new_token("KWD", model.currentToken));

            model.currentToken = "";
        }
    } else if (model.status.compare("register") == 0) {
        // register

        if (is_alphanumeric(c)) {
            model.currentToken += c;
        } else if (is_whitespace(c) || c == ',') {
            // Register
            model.tokens.push_back(
                new_token("REG", model.currentToken));

            model.currentToken = "";

            if (c == ',')
                model.status = "argument";
            else
                model.status = "default";
        }
    } else if (model.status.compare("argument") == 0) {
        // argument

        if (is_alphanumeric(c)) {
            model.currentToken += c;
        } else if (c == '$') {
            model.status = "register";
        } else if (is_whitespace(c)) {
            if (model.currentToken.length() > 0) {
                // Integer
                model.tokens.push_back(
                    new_token("INT", model.currentToken));

                model.currentToken = "";
                model.status = "default";
            }
        }

        if (last_character && model.currentToken.length() > 0) {
            if (is_numeric(model.currentToken[0])) {
                // Integer
                model.tokens.push_back(
                    new_token("INT", model.currentToken));
            } else {
                // Target
                model.tokens.push_back(
                    new_token("TAR", model.currentToken));
            }

            model.currentToken = "";
        }
    }

    return tokenize(line, model);
}
