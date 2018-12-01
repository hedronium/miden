// Copyright Miden 2018
#include <iostream>
#include "../include/tokenizer.h"
#include "../include/maybe.h"

using std::cout;
using std::endl;

// imperative
void assert_(Maybe assertion) {
    if (assertion.is(NOTHING))
        cout << ".";
    else
        cout << assertion.getValue();
}

Maybe test_label_declaration(Model model) {
    if (model.tokens[0].name == "LBL"
        && model.tokens[0].value == "main")
        return Maybe(NOTHING);
    else
        return Maybe("Label declaration failed.");
}

Maybe test_keyword(Model model) {
    if (model.tokens[0].name == "KWD"
        && model.tokens[0].value == "li")
        return Maybe(NOTHING);
    else
        return Maybe("Keyword failed.");
}

Maybe test_register(Model model) {
    if (model.tokens[1].name == "REG"
        && model.tokens[1].value == "s0")
        return Maybe(NOTHING);
    else
        return Maybe("Register failed.");
}

Maybe test_integer(Model model) {
    if (model.tokens[2].name == "INT"
        && model.tokens[2].value == "1")
        return Maybe(NOTHING);
    else
        return Maybe("Integer failed.");
}

Maybe test_target(Model model) {
    if (model.tokens[3].name == "TAR"
        && model.tokens[3].value == "done")
        return Maybe(NOTHING);
    else
        return Maybe("Target failed.");
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
