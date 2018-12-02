// Copyright Miden 2018
#include "../include/parser.h"

bool has_next_token(int token_number, Model model) {
    if ((model.tokens.size() - token_number + 1) == 0)
        return false;
    return true;
}

// add $s0, $s0, $s1
string rrr_instruction(string name, string reg_d, string reg_s1,
    string reg_s2) {
    ostringstream os;
    os << name << " " << reg_d << ", " << reg_s1 <<
        ", " << reg_s2 << endl;
        return os.str();
}

// addi $s0, $s0, 1
string rri_instruction(string name, string reg_d, string reg_s,
    string value) {
    ostringstream os;
    os << name << " " << reg_d << ", " << reg_d << ", " << value << endl;
    return os.str();
}

// li $s0, 1
string ri_instruction(string name, string reg_d, string value) {
    ostringstream os;
    os << name << " " << reg_d << ", " << value << endl;
    return os.str();
}

// j done
string j_instruction(string name, string label) {
    ostringstream os;
    os << name << " " << label << endl;
    return os.str();
}

// jr $t0
string r_instruction(string name, string reg) {
    ostringstream os;
    os << name << " " << reg << endl;
    return os.str();
}

// jr $t0
string rr_instruction(string name, string reg_d, string offset, string reg_s) {
    ostringstream os;
    os << name << " " << reg_d << " " << reg_s << "(" << offset << ")" << endl;
    return os.str();
}

// beq $s0, $t0, loop
string rrj_instruction(string name, string reg_a, string reg_b,
    string label) {
    ostringstream os;
    os << name << " " << reg_a << ", " << reg_b << ", " << label << endl;
    return os.str();
}

string parse(int token_number, Model model) {
    // not last token
    Token current_token = model.tokens[token_number];
    string parsed_output;
    int new_token_number;

    if (current_token.name.compare("LBL") == 0) {
        Label label;
        label.name = current_token.value;
        label.address = model.currentInstructionAddress;
        model.labels.push_back(label);

        new_token_number = token_number + 1;
    } else if (current_token.name.compare("KWD") == 0) {
        if (current_token.value.compare("li") == 0) {
            string reg = model.tokens[token_number + 1].value;
            string value = model.tokens[token_number + 2].value;
            parsed_output = ri_instruction(current_token.value,
                reg, value);
            new_token_number = token_number + 3;
        } else if (current_token.value.compare("addi") == 0) {
            string reg_d = model.tokens[token_number + 1].value;
            string reg_s = model.tokens[token_number + 2].value;
            string value = model.tokens[token_number + 3].value;
            parsed_output = rri_instruction(current_token.value,
                reg_d, reg_s, value);
            new_token_number = token_number + 4;
        } else if (current_token.value.compare("add") == 0) {
            string reg_d = model.tokens[token_number + 1].value;
            string reg_s1 = model.tokens[token_number + 2].value;
            string reg_s2 = model.tokens[token_number + 3].value;
            parsed_output = rrr_instruction(current_token.value,
                reg_d, reg_s1, reg_s2);
            new_token_number = token_number + 4;
        } else if (current_token.value.compare("beq") == 0) {
            string reg_a = model.tokens[token_number + 1].value;
            string reg_b = model.tokens[token_number + 2].value;
            string target = model.tokens[token_number + 3].value;
            parsed_output = rrj_instruction(current_token.value,
                reg_a, reg_b, target);
            new_token_number = token_number + 4;
        } else if (current_token.value.compare("j") == 0) {
            string target = model.tokens[token_number + 1].value;
            parsed_output = j_instruction(current_token.value, target);
            new_token_number = token_number + 2;
        } else if (current_token.value.compare("jr") == 0) {
            string reg = model.tokens[token_number + 1].value;
            parsed_output = r_instruction(current_token.value, reg);
            new_token_number = token_number + 2;
        } else if (current_token.value.compare("jal") == 0) {
            string address = model.tokens[token_number + 1].value;
            parsed_output = j_instruction(current_token.value, address);
            new_token_number = token_number + 2;
        } else if (current_token.value.compare("lw") == 0) {
            string reg_d = model.tokens[token_number + 1].value;
            string offset = model.tokens[token_number + 2].value;
            string reg_s = model.tokens[token_number + 3].value;
            parsed_output = rr_instruction(current_token.value, reg_d,
                offset, reg_s);
            new_token_number = token_number + 2;
        } else {
            new_token_number = token_number + 1;
        }

        // increment by 2 bytes (2 x 8 = 16 bits)
        model.currentInstructionAddress += 2;
    } else {
        new_token_number = token_number + 1;
    }

    // return parsed output
    if (has_next_token(new_token_number - 1, model)) {
        return parsed_output + parse(new_token_number, model);
    } else {
        return parsed_output;
    }
}
