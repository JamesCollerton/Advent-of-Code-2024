#include <iostream>
#include <sstream>
#include "../io/io.h"

struct VectorPair {
    std::vector<int> v1;
    std::vector<int> v2;
};

VectorPair convertLinesToVectorPair(std::vector<std::string> lines) {

    std::vector<int> v1;
    std::vector<int> v2;

    for (std::string s : lines) {
        
        std::stringstream ss(s);
        std::string num_string;

        bool flag = true;

        std::istringstream buffer(s);
        std::vector<std::string> ret;

        // std::copy(
        //     std::istream_iterator<std::string>(buffer), 
        //     std::istream_iterator<std::string>(),
        //     std::back_inserter(ret)
        // );

        typedef std::istream_iterator<std::string> streamiter;

        streamiter some_istream = std::istream_iterator<std::string>(buffer);
        for (streamiter it = streamiter(some_istream); it != streamiter(); it++) {
            // process words
            // if(flag) {
            //     v1.push_back(std::stoi(num_string));
            // } else {
            //     v2.push_back(std::stoi(num_string));
            // }

            // flag = !flag;
        }

        // for(auto str: ret) {
        //     std::cout << str << std::endl;
        // }
        
        // while (std::getline(ss, num_string, '\t')) {
      
        //     // std::cout << num_string << std::endl;
        //     if(flag) {
        //         v1.push_back(std::stoi(num_string));
        //     } else {
        //         v2.push_back(std::stoi(num_string));
        //     }

        //     flag = !flag;
        // }
    }

    return {
        v1,
        v2
    };
}

int main() {

    auto io = IO();
    auto lines = io.readFile("./io/day-1/input.txt");

    for(auto line: lines) {
        std::cout << line << std::endl;
    }

    auto vector_pair = convertLinesToVectorPair(lines);

    std::cout << "v1" << std::endl;
    for(auto line: vector_pair.v1) {
        std::cout << line << std::endl;
    }

    std::cout << "v2" << std::endl;
    for(auto line: vector_pair.v2) {
        std::cout << line << std::endl;
    }

    io.writeFile("./io/day-1/output.txt", lines);

    return 0;
}