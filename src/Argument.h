#pragma once

#include <string>
#include <iostream>
#include <vector>

class Argument {
public:
    Argument() = default;
    Argument(std::string);
    
    std::string value;

    enum class Type {
        KArgumentString,
        KArgumentNumber,
        kOption
    } type;

    static Argument::Type deduceType(std::string& t_value) noexcept;

    // for numbers, fold and simplify leading negatie signs
    static void simplify(std::string&) noexcept;
    void simplify() & noexcept;
};

extern std::ostream& operator<<(std::ostream&, const std::vector<Argument>&); 