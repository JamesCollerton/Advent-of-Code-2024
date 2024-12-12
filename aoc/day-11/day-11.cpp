#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../io/io.h"

using namespace std;

vector<long> parse_input(string input) {
    string temp_s;
    stringstream string_stream(input);
    vector<long> numbers;

    while(getline(string_stream, temp_s, ' ')) {
        numbers.push_back(stol(temp_s));
    }

    return numbers;
}

int count_digits(long n) {
    if (n / 10 == 0) {
        return 1;
    }
    return 1 + count_digits(n / 10);
}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-11/real-input.txt")[0];

    auto stones = parse_input(input);

    for(int counter = 0; counter < 25; counter++) {

        vector<long> new_stones;
        for(int i = 0; i < stones.size(); i++) {
            if(stones[i] == 0) {
                new_stones.push_back(1);
            } else if(count_digits(stones[i]) % 2 == 0) {
                auto long_string = to_string(stones[i]);
                auto l = long_string.substr(0, long_string.size() / 2);
                auto r = long_string.substr(long_string.size() / 2, long_string.size());
                new_stones.push_back(stol(l));
                new_stones.push_back(stol(r));
            } else {
                new_stones.push_back(stones[i] * 2024);
            }
        }
        stones = new_stones;
    }

    cout << "Part one: " << stones.size() << endl;

}

map<string, long> memoization;

long recursively_find_stones(long stone, long counter) {

    string key = to_string(stone) + "-" + to_string(counter);
    if(memoization.find(key) != memoization.end()) {
        return memoization[key];
    }

    long result;
    if(counter == 0) {
        result = 1;
    } else if(stone == 0) {
        result = recursively_find_stones(1, counter - 1);
    } else if(count_digits(stone) % 2 == 0) {
        auto long_string = to_string(stone);
        auto l = stol(long_string.substr(0, long_string.size() / 2));
        auto r = stol(long_string.substr(long_string.size() / 2, long_string.size()));
        result = recursively_find_stones(l, counter - 1) + recursively_find_stones(r, counter - 1);
    } else {
        result = recursively_find_stones(stone * 2024, counter - 1);
    }
    
    memoization[key] = result;
    return result;
}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-11/real-input.txt")[0];

    auto stones = parse_input(input);
    long total = 0;

    for(long i = 0; i < stones.size(); i++) {
        total += recursively_find_stones(stones[i], 75);
    }

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}