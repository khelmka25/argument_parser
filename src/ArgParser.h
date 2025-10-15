#pragma once

#include <iostream>
#include <format>
#include <functional>

#include "Token.h"

enum class ParseResults {
    kOkay,
    kNoArguments,
    kHelpUsed,
    kUnknownOption,
    kUnfulfilledOptions,
};

enum class OptionType {
    kHelper,
    kOptional,
    kRequired
};

class ArgParser {
public:
    ArgParser() = default;

    ArgParser(ArgParser&&) = delete;
    ArgParser(const ArgParser&) = delete;
    void operator=(ArgParser&&) = delete;
    void operator=(const ArgParser&) = delete;

protected:
    ParseResults parse(int argc, char** argv);

    std::vector<Token> tokens;
    std::unordered_map<std::string, std::vector<Token>> commands;
};