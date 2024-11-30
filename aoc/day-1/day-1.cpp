#include <iostream>
#include "../io/io.h"

int main() {

    auto io = IO();
    auto lines = io.readFile("filename");
    io.writeFile(std::vector<std::string>());

    return 0;
}