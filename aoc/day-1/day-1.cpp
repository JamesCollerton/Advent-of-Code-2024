#include <iostream>
#include <sstream>
#include "../io/io.h"

using namespace std;

typedef istream_iterator<string> streamiter;

struct VectorPair {
    vector<int> v1;
    vector<int> v2;
};

VectorPair convertLinesToVectorPair(vector<string> lines) {

    vector<int> v1;
    vector<int> v2;

    for (string s : lines) {

        bool flag = true;

        istringstream buffer(s);

        streamiter some_istream = istream_iterator<string>(buffer);
        for (streamiter it = streamiter(some_istream); it != streamiter(); it++) {
            if(flag) {
                v1.push_back(stoi(*it));
            } else {
                v2.push_back(stoi(*it));
            }

            flag = !flag;
        }
    }

    return {
        v1,
        v2
    };
}

int main() {

    auto io = IO();
    auto lines = io.readFile("./io/day-1/input.txt");

    // for(auto line: lines) {
    //     cout << line << endl;
    // }

    auto vector_pair = convertLinesToVectorPair(lines);

    sort(vector_pair.v1.begin(), vector_pair.v1.end());
    sort(vector_pair.v2.begin(), vector_pair.v2.end()) ;

    int total = 0;

    for(int i = 0; i < vector_pair.v1.size(); i++) {
        total += abs(vector_pair.v1[i] - vector_pair.v2[i]);
    }

    cout << total << endl;

    // cout << "v1" << endl;
    // for(auto line: vector_pair.v1) {
    //     cout << line << endl;
    // }

    // cout << "v2" << endl;
    // for(auto line: vector_pair.v2) {
    //     cout << line << endl;
    // }

    // io.writeFile("./io/day-1/output.txt", lines);

    return 0;
}