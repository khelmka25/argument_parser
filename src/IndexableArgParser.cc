#include "IndexableArgParser.h"

std::vector<Argument>& IndexibleArgParser::operator[](std::initializer_list<std::string> options) {
    for (auto& option : options) {
        if (parameterOptionMap.find(option) != parameterOptionMap.end()) {
            return parameterOptionMap[option];
        }
    }
    return empty_set;
}