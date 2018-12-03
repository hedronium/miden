// Copyright Miden 2018
#ifndef MIDEN_INCLUDE_MAYBE_H_
#define MIDEN_INCLUDE_MAYBE_H_

#define NOTHING ""

#include <string>
#include "../include/tokenizer.h"

using std::string;

template <class T>
class Maybe {
    bool nothing;
 public:
    T value;

    explicit Maybe(T);
    Maybe();
    bool is(string);
};

#endif  // MIDEN_INCLUDE_MAYBE_H_
