#include "io.h"

std::vector<std::string> IO::readFile(const std::string &filename) const {

    std::string line;
    std::vector<std::string> lines;
    std::ifstream file(filename);

    if(!file) {
        std::cout << "Error opening input file: " << filename << std::endl;
        throw(-1);
    }

    while (std::getline(file, line)){
        lines.push_back(line);
    }

    return lines;
}

void IO::writeFile(const std::string &filename, const std::vector<std::string> file_contents) const {

    std::ofstream file(filename);

    if(!file) {
        std::cout << "Error opening output file: " << filename << std::endl;
        throw(-1);
    }

    std::ostream_iterator<std::string> iterator(file, "\n");
    std::copy(std::begin(file_contents), std::end(file_contents), iterator);
}