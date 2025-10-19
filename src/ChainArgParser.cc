#include "ChainArgParser.h"

void ChainArgParser::registerHandler(std::initializer_list<std::string> options, std::function<void(std::vector<Argument>&)>&& callback, OptionType optionType) noexcept {
    for (auto& item : options) {
        callbackMapper[item] = callbackDescriptors.size();
    }

    callbackDescriptors.emplace_back(std::move(callback), optionType);

    if (optionType == OptionType::kRequired) {
        nRequiredOptions++;
    }
}

ParseResults ChainArgParser::parse(int argc, char** argv) noexcept {
    this->ArgParser::parse(argc, argv);

    for (auto& [option, args] : parameterOptionMap) {
        if (callbackMapper.find(option) != callbackMapper.end()) {
            CallbackDescriptor& descriptor = getDescriptor(option);

            /* Already consumed option? */
            if (descriptor.consumed) {
                std::cout << std::format("Duplicate option: {}, args: ", option) << args << std::endl;
                continue;
            }

            descriptor.callback(args);
            descriptor.consumed = true;

            if (descriptor.optionType == OptionType::kHelper) {
                return ParseResults::kHelpUsed;
            }

            if (descriptor.optionType == OptionType::kRequired) {
                nRequiredOptions--;
            }
        }
        else {
            std::cout << std::format("Unknown or unregistered option: {}, args:", option) << args << std::endl;
            return ParseResults::kUnknownOption;
        }
    }

    // ensure all required options are consumed
    if (nRequiredOptions != 0ull) {
        std::cout << std::format("Unfilled required options:") << std::endl;
        for (auto& [option, args] : parameterOptionMap) {
            if (callbackMapper.find(option) != callbackMapper.end()) {
                CallbackDescriptor& descriptor = getDescriptor(option);
                if (descriptor.optionType == OptionType::kRequired && !descriptor.consumed) {
                    std::cout << std::format("option: {}, args:", option) << args << std::endl;
                }
            }
        }

        return ParseResults::kUnfulfilledOptions;
    }

    return ParseResults::kOkay;
}

CallbackDescriptor& ChainArgParser::getDescriptor(const std::string& option) noexcept {
    std::size_t index = callbackMapper.at(option);
    return callbackDescriptors.at(index);
}