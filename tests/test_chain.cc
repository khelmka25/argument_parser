
#include "ChainArgParser.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Chain Test") {

    int argc = 5;
    const char* argv[] = {
        "/build/a.exe",
        "--add",
        "8",
        "-4",
        "--2"
    };

    ChainArgParser parser;
    parser.registerHandler({ "-a", "--add", "--sum" }, [](std::vector<Argument>& args) {
        int sum = 0;
        for (auto& arg : args) {
            sum += std::stoi(arg.value);
        }

        REQUIRE(sum == 6);
    }, OptionType::kOptional);

    parser.parse(argc, (char**)argv);

}