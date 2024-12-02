#include <iostream>
#include <sstream>
#include "../io/io.h"

using namespace std;

typedef istream_iterator<string> streamiter;

bool isReportSafe(std::string report) {

    istringstream buffer(report);
    streamiter istream = istream_iterator<string>(buffer);

    bool increasing = true;

    streamiter it = streamiter(istream);
    auto firstNum = stoi(*it++);
    auto secondNum = stoi(*it);

    if(firstNum < secondNum) {
        increasing = true;
    } else if(firstNum > secondNum) {
        increasing = false;
    } else {
        return false;
    }

    int prev = firstNum;

    for (it; it != streamiter(); it++) {
        auto num = stoi(*it);

        if((num < prev && increasing) || (num > prev && !increasing) || num == prev || (abs(num - prev) > 3)) {
            return false;
        }

        prev = num;
    }

    return true;
}

void partOne() {

    const auto io = IO();
    const auto lines = io.readFile("./io/day-2/real-input.txt");

    auto total = 0;

    for (string s : lines) {
        if(isReportSafe(s)) {
            total++;
        }
    }

    cout << "Part one: " << total << endl;

}

void partTwo() {

    const auto io = IO();
    const auto lines = io.readFile("./io/day-2/real-input.txt");

    auto total = 0;

    for (string s : lines) {

        bool is_safe = false;

        for(int i = 0; i < s.length(); i++) {
            if(s[i] != ' ') {
                auto sc = string(s);
                sc.erase(sc.begin() + i);

                // cout << sc << endl;

                if(isReportSafe(sc)) {
                    is_safe = true;
                }
            }
        }

        if(is_safe || isReportSafe(s)) {
            total++;
        }
    }

    cout << "Part two: " << total << endl;

}

int main() {

    partOne();
    partTwo();

    return 0;
}