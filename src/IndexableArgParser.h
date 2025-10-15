#pragma once

#include "ArgParser.h"

class IndexibleArgParser : private ArgParser {
public:
    using ArgParser::parse;
    std::vector<Token>& operator[](std::initializer_list<std::string>);
private:
    std::vector<Token> empty_set;
};