#include "ArgParser.h"

ParseResults ArgParser::parse(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "Invalid usage. Use -h for help" << std::endl;
        return ParseResults::kNoArguments;
    }

    // create tokens
    tokens.clear();
    tokens.reserve(argc - 1);

    for (int i = 0; i < argc; i++) {
        std::string value(argv[i]);
        tokens.emplace_back(std::move(value));
    }

    // create options
    commands.clear();

    bool optionHasArguments = true;
    Token& lastOption = tokens.front();
    Token& lastArg = tokens.back();

    for (auto& token : tokens) {
        switch (token.type) {
        case Token::Type::kOption: {
            // before losing the previous token if it did not have any arguments
            if (!optionHasArguments) {
                commands[lastOption.value].clear();
            }

            optionHasArguments = false;
            lastOption = token;
            break;
        }
        default:
        case Token::Type::KArgumentNumber:
        case Token::Type::KArgumentString: {
            // commit this current argument to the current option
            commands[lastOption.value].push_back(token.value);

            optionHasArguments = true;
            lastArg = token;
            break;
        }
        }
    }

    if (!optionHasArguments) {
        commands[lastOption.value].clear();
    }

    return ParseResults::kOkay;
}
