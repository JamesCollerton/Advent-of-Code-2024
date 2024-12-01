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

        streamiter istream = istream_iterator<string>(buffer);
        for (streamiter it = streamiter(istream); it != streamiter(); it++) {
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

    const auto io = IO();
    const auto lines = io.readFile("./io/day-1/test-input.txt");

    const auto vector_pair = convertLinesToVectorPair(lines);
    auto v1 = move(vector_pair.v1);
    auto v2 = move(vector_pair.v2);

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end()) ;

    int total = 0;

    for(int i = 0; i < v1.size(); i++) {
        total += abs(v1[i] - v2[i]);
    }

    cout << total << endl;

    return 0;
}