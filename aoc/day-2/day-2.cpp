#include <iostream>
#include <sstream>
// #include <bits/stdc++.h>
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
        string temp_s;
        stringstream ss(s);
        vector<string> v;

        while(getline(ss, temp_s, ' ')) {
            v.push_back(temp_s);
        }

        for(int i = 0; i < v.size(); i++) {

            string new_s = "";

            for(int j = 0; j < v.size(); j++) {
                if(i != j) {
                    new_s += " " + v[j];
                }
            }

            if(isReportSafe(new_s)) {
                is_safe = true;
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