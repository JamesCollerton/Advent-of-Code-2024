#include <iostream>
#include "../io/io.h"

int main() {

    auto io = IO();
    auto lines = io.readFile("./io/day-1/input.txt");

    for(auto line: lines) {
        std::cout << line << std::endl;
    }

    io.writeFile("./io/day-1/output.txt", lines);

    return 0;
}