#pragma once

#include <algorithm>
#include <initializer_list>
#include <string>
#include <functional>
#include <format>
#include <iostream>

#include "ArgParser.h"

struct CallbackDescriptor {
    CallbackDescriptor() = default;
    CallbackDescriptor(std::function<void(std::vector<Token>& args)>&& t_callback, OptionType t_optionType) {
        callback = std::move(t_callback);
        optionType = t_optionType;
    }
    std::function<void(std::vector<Token>& args)> callback;
    OptionType optionType;
    bool consumed;
};

class ChainArgParser : protected ArgParser {
public:
    ChainArgParser() = default;

    ChainArgParser(ChainArgParser&&) = delete;
    ChainArgParser(const ChainArgParser&) = delete;
    void operator=(ChainArgParser&&) = delete;
    void operator=(const ChainArgParser&) = delete;

    ParseResults parse(int argc, char** argv) noexcept;
    void registerHandler(std::initializer_list<std::string>, std::function<void(std::vector<Token>&)>&&, OptionType = OptionType::kOptional) noexcept;

private:
    // Maps options to functional callbacks
    std::unordered_map<std::string, std::size_t> callbackMapper;
    std::vector<CallbackDescriptor> callbackDescriptors;
    std::size_t nRequiredOptions;

    CallbackDescriptor& getDescriptor(const std::string&) noexcept;
};