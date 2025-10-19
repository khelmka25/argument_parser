#include "ArgParser.h"

ParseResults ArgParser::parse(int argc, char** argv) {
    if (argc <= 1) {
        std::cout << "Invalid usage. Use -h for help" << std::endl;
        return ParseResults::kNoArguments;
    }

    // create arguments
    std::vector<Argument> arguments;
    arguments.reserve(argc - 1);

    for (int i = 1; i < argc; i++) {
        Argument arg(argv[i]);
        arguments.push_back(arg);
    }

    // create options
    parameterOptionMap.clear();

    Argument* lastOption = &arguments.front();
    Argument* lastParam = &arguments.back();
    bool optionHasParameters = true;

    for (auto& argument : arguments) {
        switch (argument.type) {
            case Argument::Type::kOption: {
                // before losing the previous token if it did not have any arguments
                if (!optionHasParameters) {
                    parameterOptionMap[lastOption->value] = {};
                }

                optionHasParameters = false;
                lastOption = &argument;
                break;
            }
            default:
            case Argument::Type::KArgumentNumber:
            case Argument::Type::KArgumentString: {
                // commit this current argument to the current option
                parameterOptionMap[lastOption->value].push_back(argument.value);

                optionHasParameters = true;

                lastParam = &argument;
                break;
            }
        }
    }

    if (!optionHasParameters) {
        parameterOptionMap[lastOption->value] = {};
    }

    return ParseResults::kOkay;
}
