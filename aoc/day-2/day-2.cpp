#include <iostream>
#include <sstream>
#include "../io/io.h"

using namespace std;

typedef istream_iterator<string> streamiter;

bool isReportSafe(std::string report) {

    istringstream buffer(report);
    streamiter istream = istream_iterator<string>(buffer);

    int prev = -1;
    bool increasing = true;

    // Decide if increasing/ decreasing
    // Check absolute difference

    for (streamiter it = streamiter(istream); it != streamiter(); it++) {
        auto num = stoi(*it);
        // For first item, check the next one to see if it's greater or smaller
        if(prev == -1) {
            prev = num;
            auto nextNum = stoi(*next(it, 1));
            if(num < nextNum) {
                increasing = false;
            } else if(num > nextNum) {
                increasing = true;
            } else {
                return false;
            }
        // Otherwise check 
        } else {
            if((num < prev && increasing) || (num > prev && !increasing) || num == prev) {
                return false;
            }
        }
        prev = num;
    }

    return true;
}

int main() {

    const auto io = IO();
    const auto lines = io.readFile("./io/day-2/test-input.txt");

    auto total = 0;

    for (string s : lines) {
        if(isReportSafe(s)) {
            total++;
        }
    }

    cout << total << endl;

    return 0;
}