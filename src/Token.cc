#include "Token.h"

Token::Token(std::string t_value)
    : value(std::move(t_value))
    , type(deduceType(value)) {
    // determine the type of the token
    // trim leading negatives if necessary
    if (type == Type::KArgumentNumber) {
        simplify();
    }
}

/*
examples of options
-a
-add
-add-evens
--add-odds
--
-a1

not options (numbers)
-3
--454 => trim to -454
--23-2 => trim to 23-2
-3-2
*/
Token::Type Token::deduceType(std::string& t_value) const noexcept {
    if (t_value.empty()) {
        return Token::Type::KArgumentString;
    }

    // the general format is one or two dashes followed by at least one alphabet character
    const char* const str = t_value.c_str();
    const char* ptr = str;
    // normal string, eg. abcd or 1234
    if (std::isalpha(*ptr)) {
        return Token::Type::KArgumentString;
    }

    // walk the string until it is not a dash
    do {
        if (*ptr != '-') {
            break;
        }
    } while (*++ptr != 0);

    // now check that the ptr is now only alphanumeric
    if (std::isalpha(*ptr)) {
        return Token::Type::kOption;
    }

    // else: a number
    return Token::Type::KArgumentNumber;
}

void Token::simplify() noexcept {
    // simplify leading negative signs
    // eg. ---1 -> -1 or --2 -> 2
    const char* const str = value.c_str();
    const char* ptr = str;
    do {
        if (*ptr != '-') {
            break;
        }
    } while (*++ptr != 0);

    // eg.
    // -----65
    // |    ^ ptr
    // ^ str
    // ptr - str = 5 -> 5 dashes
    // simplify to 1 dash: remove 4
    int distance = int(ptr - str);

    std::string replacement;
    std::copy(std::next(value.begin(), distance - 1), value.end(), replacement.begin());
    value = std::move(replacement);
}

std::ostream& operator<<(std::ostream& stream, const std::vector<Token>& tokens) {
    for (auto& token : tokens) {
        stream << token.value << std::endl;
    }
    return stream;
}
