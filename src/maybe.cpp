// Copyright Miden 2018

#include "../include/maybe.h"

Maybe::Maybe(string value) {
    this->value = value;
}

bool Maybe::is(string is) {
    if (is == NOTHING)
        return this->value == NOTHING;
    return this->value != NOTHING;
}

string Maybe::getValue() {
    return this->value;
}
