// Copyright Miden 2018
#ifndef MIDEN_INCLUDE_MAYBE_H_
#define MIDEN_INCLUDE_MAYBE_H_

#define NOTHING ""
#define JUST "__JUST__"

#include <string>

using std::string;

class Maybe {
    string value;
 public:
    explicit Maybe(string);

    bool is(string);

    string getValue();
};

#endif  // MIDEN_INCLUDE_MAYBE_H_
