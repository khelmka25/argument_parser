#include "Argument.h"

Argument::Argument(std::string t_value)
    : value(t_value)
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
/*static*/
Argument::Type Argument::deduceType(std::string& value)  noexcept {
    if (value.empty()) {
        return Argument::Type::KArgumentString;
    }

    const char* const str = value.c_str();
    const char* ptr = str;
    
    // consume all the dashes:
    do {
        if (*ptr != '-') {
            break;
        }
    } while (*++ptr != 0);

    // check if next non dash character is a alpha
    if (std::isalpha(*ptr)) {
        // if any dashes were consumed
        if (ptr - str > 0) {
            return Argument::Type::kOption;
        }
        return Argument::Type::KArgumentString;
    }

    // else: a number
    return Argument::Type::KArgumentNumber;
}

void Argument::simplify(std::string& value) noexcept {

    const char* const str = value.c_str();
    const char* ptr = str;
    
    // consume all the dashes:
    do {
        if (*ptr != '-') {
            break;
        }
    } while (*++ptr != 0);

    auto distance = ptr - str;

    // vales of 0 or 1 do not require simplification
    if (distance < 2) {
        return;
    }

    auto toRemove = distance;
    if (distance & 1) {
        toRemove--;    
    }

    // eg.
    // -----65
    // |    ^ ptr
    // ^ str
    // ptr - str = 5 -> 5 dashes
    // simplify to 1 dash: remove 4
    value.erase(0ull, toRemove);
}

void Argument::simplify() & noexcept {
    simplify(value);
}

std::ostream& operator<<(std::ostream& stream, const std::vector<Argument>& tokens) {
    for (auto& token : tokens) {
        stream << token.value << std::endl;
    }
    return stream;
}
