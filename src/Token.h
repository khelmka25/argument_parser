#pragma once

#include <string>
#include <iostream>
#include <vector>

class Token {
public:
    Token() = default;
    Token(std::string);
    
    std::string value;

    enum class Type {
        KArgumentString,
        KArgumentNumber,
        kOption
    } type;

    Token::Type deduceType(std::string& t_value) const noexcept;

    // for numbers, fold and simplify leading negatie signs
    void simplify() noexcept;
};

extern std::ostream& operator<<(std::ostream&, const std::vector<Token>&); 