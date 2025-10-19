
#include "IndexableArgParser.h"

void indexTest(int argc, char** argv) {

    IndexibleArgParser parser;
    parser.parse(argc, argv);

    if (auto& args = parser[{"-a", "--add", "--sum"}]; !args.empty()) {
        int sum = 0;
        for (auto& arg : args) {
            int v = std::stoi(arg.value);
            sum += v;
        }

        std::cout << sum << std::endl;
    }
}