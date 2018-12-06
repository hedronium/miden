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

    Label multiplyNumbers;
    multiplyNumbers.name = "multiplyNumbers";
    multiplyNumbers.address = 1;

    model.labels.push_back(multiplyNumbers);

    return model;
}

Model add_addi_tokens(Model model) {
    // addi
    model.tokens.push_back(
        create_keyword("addi"));

    // $s0
    model.tokens.push_back(
        create_register("s0"));

    // $t0
    model.tokens.push_back(
        create_register("t0"));

    // 1
    model.tokens.push_back(
        create_integer("1"));

    return model;
}

Model add_j_tokens(Model model) {
    // j
    model.tokens.push_back(
        create_keyword("j"));

    // multiplyNumbers
    model.tokens.push_back(
        create_keyword("multiplyNumbers"));

    Label multiplyNumbers;
    multiplyNumbers.name = "multiplyNumbers";
    multiplyNumbers.address = 2;

    model.labels.push_back(multiplyNumbers);

    return model;
}

Model add_beq_tokens(Model model) {
    // beq
    model.tokens.push_back(
        create_keyword("beq"));

    // $s0
    model.tokens.push_back(
        create_register("s0"));

    // $t0
    model.tokens.push_back(
        create_register("t0"));

    // done
    model.tokens.push_back(
        create_keyword("done"));

    Label done;
    done.name = "done";
    done.address = 3;

    model.labels.push_back(done);

    return model;
}

Model add_add_tokens(Model model) {
    // add
    model.tokens.push_back(
        create_keyword("add"));

    // $s0
    model.tokens.push_back(
        create_register("s0"));

    // $t0
    model.tokens.push_back(
        create_register("t0"));

    // $v0
    model.tokens.push_back(
        create_register("v0"));

    return model;
}

Model add_jr_tokens(Model model) {
    // jr
    model.tokens.push_back(
        create_keyword("jr"));

    // $ra
    model.tokens.push_back(
        create_keyword("ra"));

    return model;
}

Maybe<string> test_li(string output) {
    if (!output.compare("0110010000000001"))
        return Maybe<string> ();
    else
        return Maybe<string> ("li failed.");

    return Maybe<string> ();
}

Maybe<string> test_jal(string output) {
    if (!output.compare("1010000000000001"))
        return Maybe<string> ();
    else
        return Maybe<string> ("jal failed.");
}

Maybe<string> test_addi(string output) {
    if (!output.compare("0010010100000001"))
        return Maybe<string> ();
    else
        return Maybe<string> ("addi failed.");
}

Maybe<string> test_j(string output) {
    if (!output.compare("1000000000000010"))
        return Maybe<string> ();
    else
        return Maybe<string> ("j failed.");
}

Maybe<string> test_beq(string output) {
    if (!output.compare("0100010100000011"))
        return Maybe<string> ();
    else
        return Maybe<string> ("beq failed.");
}

Maybe<string> test_add(string output) {
    if (!output.compare("0000010100000011"))
        return Maybe<string> ();
    else
        return Maybe<string> ("add failed.");
}

Maybe<string> test_jr(string output) {
    if (!output.compare("1100000000000110"))
        return Maybe<string> ();
    else
        return Maybe<string> ("jr failed.");
}

int main() {
    // initial model
    Model initialModel;
    initialModel.status = "default";
    initialModel.currentToken = "";
    initialModel.currentInstructionAddress = 0;

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

    // addi
    model = add_addi_tokens(model);

    assert_(
        test_addi(
            parse(model)));

    // reset model
    model = initialModel;

    // j
    model = add_j_tokens(model);

    assert_(
        test_j(
            parse(model)));

    // reset model
    model = initialModel;

    // beq
    model = add_beq_tokens(model);

    assert_(
        test_beq(
            parse(model)));

    // reset model
    model = initialModel;

    // add
    model = add_add_tokens(model);

    assert_(
        test_add(
            parse(model)));

    // reset model
    model = initialModel;

    // jr
    model = add_jr_tokens(model);

    assert_(
        test_jr(
            parse(model)));

    // reset model
    model = initialModel;

    cout << endl;

    return 0;
}
