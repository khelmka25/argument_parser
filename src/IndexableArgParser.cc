#include "IndexableArgParser.h"

std::vector<Token>& IndexibleArgParser::operator[](std::initializer_list<std::string> options) {
    for (auto& option : options) {
        if (commands.find(option) != commands.end()) {
            return commands[option];
        }
    }
    return empty_set;
}