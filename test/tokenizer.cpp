// Copyright Miden 2018
#include <iostream>
#include <string>
#include "../include/tokenizer.h"
#include "../include/maybe.h"

using std::cout;
using std::endl;
using std::string;

// imperative
void debug_token(Token token) {
    cout << token.name << " = " << token.value << endl;
}

void debug_tokens(Model model) {
    cout << model.tokens.size() << " tokens." << endl;
    for (int i = 0; i < model.tokens.size(); i++)
        debug_token(model.tokens[i]);
}

void assert_(Maybe<string> assertion) {
    if (assertion.is(NOTHING))
        cout << ".";
    else
        cout << assertion.value;
}

// functional
Maybe<string> test_label_declaration(Model model) {
    if (!model.tokens[0].name.compare("LBL")
        && !model.tokens[0].value.compare("main"))
        return Maybe<string> ();
    else
        return Maybe<string> ("Label declaration failed.");
}

Maybe<string> test_keyword(Model model) {
    if (!model.tokens[0].name.compare("KWD")
        && !model.tokens[0].value.compare("li"))
        return Maybe<string> ();
    else
        return Maybe<string> ("Keyword failed.");
}

Maybe<string> test_register(Model model) {
    if (!model.tokens[1].name.compare("REG")
        && !model.tokens[1].value.compare("s0"))
        return Maybe<string> ();
    else
        return Maybe<string> ("Register failed.");
}

Maybe<string> test_integer(Model model) {
    if (!model.tokens[2].name.compare("INT")
        && !model.tokens[2].value.compare("1"))
        return Maybe<string> ();
    else
        return Maybe<string> ("Integer failed.");
}

Maybe<string> test_target(Model model) {
    if (!model.tokens[3].name.compare("TAR")
        && !model.tokens[3].value.compare("done"))
        return Maybe<string> ();
    else
        return Maybe<string> ("Target failed.");
}

int main() {
    // setup model
    Model model;
    model.status = "default";
    model.currentToken = "";

    // Label
    assert_(
        test_label_declaration(
            tokenize("main:", model)));

    // Keyword
    assert_(
        test_keyword(
            tokenize("li $s0, 1", model)));

    // Register
    assert_(
        test_register(
            tokenize("li $s0, 1", model)));

    // Integer
    assert_(
        test_integer(
            tokenize("li $s0, 1", model)));

    // Target
    assert_(
        test_target(
            tokenize("beq $t0, $s0, done", model)));

    cout << endl;

    return 0;
}
