#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

typedef istream_iterator<string> streamiter;

class Parsing {

    public:

        struct VectorPair {
            vector<int> v1;
            vector<int> v2;
        };

        static VectorPair convertLinesToVectorPair(vector<string> lines);
};