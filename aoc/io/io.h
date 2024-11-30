#include<vector>
#include<iostream>

class IO {
    public:
        std::vector<std::string> readFile(std::string filename);
        void writeFile(std::vector<std::string> file_contents);
};