// Copyright Miden 2018
#include "../include/maybe.h"

template <class T>
Maybe<T>::Maybe(T value) {
    this->nothing = false;
    this->value = value;
}

template <class T>
Maybe<T>::Maybe() {
    this->nothing = true;
}

template <class T>
bool Maybe<T>::is(string is) {
    if (is == NOTHING)
        return this->nothing;
    else
        return !this->nothing;
}

template class Maybe<string>;
template class Maybe<Label>;
