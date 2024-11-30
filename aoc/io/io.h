#include <vector>
#include <iostream>
#include <fstream>


class IO {
    public:
        std::vector<std::string> readFile(const std::string &filename) const;
        void writeFile(const std::string &filename, const std::vector<std::string> file_contents) const;
};