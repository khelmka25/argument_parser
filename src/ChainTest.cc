
#include "ChainArgParser.h"

void chainTest(int argc, char** argv) {

    ChainArgParser parser;
    parser.registerHandler({ "-a", "--add", "--sum" }, [](std::vector<Token>& args) {
        int sum = 0;
        for (auto& arg : args) {
            sum += std::stoi(arg.value);
        }

        std::cout << sum << std::endl;
    }, OptionType::kOptional);

    parser.parse(argc, argv);
}