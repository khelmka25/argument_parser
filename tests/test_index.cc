
#include "IndexableArgParser.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Index Test") {

    int argc = 5;
    const char* argv[] = {
        "/build/a.exe",
        "--add",
        "8",
        "-4",
        "--2"
    };

    IndexibleArgParser parser;
    parser.parse(argc, (char**)argv);

    if (auto& args = parser[{"-a", "--add", "--sum"}]; !args.empty()) {
        int sum = 0;
        for (auto& arg : args) {
            int v = std::stoi(arg.value);
            sum += v;
        }
        
        REQUIRE(sum == 6);
    }
}