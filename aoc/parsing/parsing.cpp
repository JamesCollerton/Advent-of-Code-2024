#include "parsing.h"

static Parsing::VectorPair convertLinesToVectorPair(vector<string> lines) {

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