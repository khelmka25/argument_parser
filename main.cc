#include <iostream>

extern void indexTest(int argc, char** argv);
extern void chainTest(int argc, char** argv);

int main(int argc, char** argv) {
    
    std::cout << "Index Test Results: " << std::endl;
    indexTest(argc, argv);

    std::cout << "Chain Test Results: " << std::endl;
    chainTest(argc, argv);

    return 0;
}

