// Copyright Miden 2018
#include <iostream>
#include <string>
#include "../include/label.h"
#include "../include/parser.h"
#include "../include/maybe.h"

using std::cout;
using std::endl;
using std::string;

// imperative
void assert_(Maybe<string> assertion) {
    if (assertion.is(NOTHING))
        cout << ".";
    else
        cout << assertion.value;
}

// functional
Maybe<string> test_li(string output) {
    if (!output.compare("0110010000000001"))
        return Maybe<string> ();
    else
        return Maybe<string> ("li failed.");

    return Maybe<string> ();
}

Maybe<string> test_jal(string output) {
    if (!output.compare("0110010000000001"))
        return Maybe<string> ();
    else
        return Maybe<string> ("jal failed.");

    return Maybe<string> ();
}

Token create_token(string name, string value) {
    Token token;
    token.name = name;
    token.value = value;
    return token;
}

Token create_keyword(string name) {
    return create_token("KWD", name);
}

Token create_register(string name) {
    return create_token("REG", name);
}

Token create_integer(string value) {
    return create_token("INT", value);
}

Model add_li_tokens(Model model) {
    // li
    model.tokens.push_back(
        create_keyword("li"));

    // $s0
    model.tokens.push_back(
        create_register("s0"));

    // 1
    model.tokens.push_back(
        create_integer("1"));

    return model;
}

Model add_jal_tokens(Model model) {
    // jal
    model.tokens.push_back(
        create_keyword("jal"));

    // multiplyNumbers
    model.tokens.push_back(
        create_keyword("multiplyNumbers"));

    return model;
}

int main() {
    // initial model
    Model initialModel;
    initialModel.status = "default";
    initialModel.currentToken = "";

    // setup model as initial model
    Model model = initialModel;

    // li
    model = add_li_tokens(model);

    assert_(
        test_li(
            parse(model)));

    // reset model
    model = initialModel;

    // jal
    model = add_jal_tokens(model);

    assert_(
        test_jal(
            parse(model)));

    // reset model
    model = initialModel;

    cout << endl;

    return 0;
}
