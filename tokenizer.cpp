bool numeric(char c) {
    if (c >= 48 && c <= 57)
        return true;
    return false;
}

bool alphabetic(char c) {
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        return true;
    return false;
}

bool alphanumeric(char c) {
    return alphabetic(c) || numeric(c);
}

bool whitespace(char c) {
    if (c == 32 || c == 9 || c == 10)
        return true;
    return false;
}

struct Token {
    string name;
    string value;
};