// Copyright Miden 2018
#include "../include/parser.h"

bool has_next_token(int token_number, Model model) {
    if ((model.tokens.size() - token_number + 1) == 0)
        return false;
    return true;
}

string opcode(string name) {
    if (!name.compare("add"))
        return "000";
    else if (!name.compare("addi"))
        return "001";
    else if (!name.compare("beq"))
        return "010";
    else if (!name.compare("li"))
        return "011";
    else if (!name.compare("j"))
        return "100";
    else if (!name.compare("jal"))
        return "101";
    else if (!name.compare("jr"))
        return "110";
    else
        return "111";
}

string register_(string name) {
    if (!name.compare("0"))
        return "000";
    else if (!name.compare("s0"))
        return "001";
    else if (!name.compare("t0"))
        return "010";
    else if (!name.compare("v0"))
        return "011";
    else if (!name.compare("a0"))
        return "100";
    else if (!name.compare("a1"))
        return "101";
    else if (!name.compare("ra"))
        return "110";
    else
        return "111";
}

Maybe<Label> label_search(string name, Model model, int count) {
    if (model.labels[count].name == name)
        return Maybe<Label> (model.labels[count]);
    else if ((count + 1) != model.labels.size())
        return label_search(name, model, count + 1);
    else
        return Maybe<Label> ();
}

string label_address(string name, Model model) {
    Maybe<Label> result = label_search(name, model, 0);
    if (result.is(NOTHING))
        return "";
    else
        return to_string(result.value.address);
}

string zeros(int n) {
    if (n == 0)
        return "";
    return "0" + zeros(n - 1);
}

string fixed_size_binary(string immediate, int size) {
    int extra_bits = size - immediate.size();

    if (extra_bits == 1)
        return "0" + immediate;
    else
        return "0" + fixed_size_binary(immediate, size - 1);
}

string decimal_to_binary(int decimal, string binary) {
    int division_result = static_cast<int>(decimal / 2);
    int remainder = static_cast<int>(decimal % 2);

    string new_binary = to_string(remainder) + binary;

    if (division_result == 0) {
        return new_binary;
    } else {
        return decimal_to_binary(division_result, new_binary);
    }
}

string decimal_to_binary(string decimal) {
    return decimal_to_binary(stoi(decimal), "");
}

// add $s0, $s0, $s1
string rrr_instruction(string name, string reg_d, string reg_s,
    string reg_t) {
    ostringstream os;
    os << opcode(name) << register_(reg_d) << register_(reg_s)
        << zeros(4) << register_(reg_t) << endl;
        return os.str();
}

// addi $s0, $s0, 1
string rri_instruction(string name, string reg_d, string reg_s,
    string value) {
    ostringstream os;
    os << opcode(name) << register_(reg_d) <<
        register_(reg_d)
        << fixed_size_binary(
            decimal_to_binary(value), 7) << endl;
    return os.str();
}

// li $s0, 1
string ri_instruction(string name, string reg_d, string value) {
    ostringstream os;
    os << opcode(name) << register_(reg_d) <<
        fixed_size_binary(
            decimal_to_binary(value), 10) << endl;
    return os.str();
}

// j done
string j_instruction(string name, string target) {
    ostringstream os;
    os << opcode(name)
        << fixed_size_binary(
            decimal_to_binary(target), 13) << endl;
    return os.str();
}

// jr $t0
string r_instruction(string name, string reg) {
    ostringstream os;
    os << opcode(name) << zeros(10) << register_(reg) << endl;
    return os.str();
}

// // jr $t0
// string rr_instruction(string name, string reg_d, string offset,
//     string reg_s) {
//     ostringstream os;
//     os << opcode(name) << " " << register_(reg_d) << " "
//         << register_(reg_s) << "(" <<
//         offset << ")" << endl;
//     return os.str();
// }

// beq $s0, $t0, loop
string rrj_instruction(string name, string reg_a, string reg_b,
    string target) {
    ostringstream os;
    os << opcode(name) << register_(reg_a)
        << register_(reg_b)
        << fixed_size_binary(
            decimal_to_binary(target), 7)
        << endl;
    return os.str();
}

string parse(int token_number, Model model) {
    // not last token
    Token current_token = model.tokens[token_number];
    string parsed_output;
    int new_token_number;

    if (current_token.name.compare("KWD") == 0) {
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
            string target = label_address(
                model.tokens[token_number + 3].value, model);
            parsed_output = rrj_instruction(current_token.value,
                reg_a, reg_b, target);
            new_token_number = token_number + 4;
        } else if (current_token.value.compare("j") == 0) {
            string target = label_address(
                model.tokens[token_number + 1].value, model);
            parsed_output = j_instruction(current_token.value, target);
            new_token_number = token_number + 2;
        } else if (current_token.value.compare("jr") == 0) {
            string reg = model.tokens[token_number + 1].value;
            parsed_output = r_instruction(current_token.value, reg);
            new_token_number = token_number + 2;
        } else if (current_token.value.compare("jal") == 0) {
            string target = label_address(
                model.tokens[token_number + 1].value, model);
            parsed_output = j_instruction(current_token.value, target);
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

string parse(Model model) {
    return parse(0, model);
}
