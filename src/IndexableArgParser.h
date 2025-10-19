#pragma once

#include "ArgParser.h"

class IndexibleArgParser : private ArgParser {
public:
    using ArgParser::parse;
    std::vector<Argument>& operator[](std::initializer_list<std::string>);

private:
    std::vector<Argument> empty_set;
};