#pragma once

#include <iostream>
#include <format>
#include <functional>

#include "Argument.h"

// Terminology
// Argument is anything passed in via the command line
// Option is anything like -O3 or --verbose
// Parameter is any string, path, or numerical value passed in after
// an option
// There may be zero or more parameters for an option

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

    std::unordered_map<std::string, std::vector<Argument>> parameterOptionMap;
};