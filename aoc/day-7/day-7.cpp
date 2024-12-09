#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../io/io.h"

using namespace std;

struct Entry {
    long total;
    vector<long> numbers;
};

vector<Entry> parse_input(const vector<string> &input) {

    vector<Entry> entries;

    for(auto line: input) {
        const auto total = stol(line.substr(0, line.find(':')));
        const auto right = line.substr(line.find(':') + 2);

        string temp_s;
        stringstream string_stream(right);
        vector<long> numbers;

        while(getline(string_stream, temp_s, ' ')) {
            numbers.push_back(stol(temp_s));
        }

        entries.emplace_back(Entry{
            total,
            numbers
        });
    }

    return entries;
}

void print(vector<Entry> entries) {

    for(auto entry: entries) {
        cout << entry.total << ": ";
        for(auto n: entry.numbers) {
            cout << n << " ";
        }
        cout << endl;
    }

}

void recursively_solve(long rt, int pos, const vector<long> &numbers, set<long> &totals) {
    if(pos >= numbers.size()) {
        totals.insert(rt);
    } else {
        recursively_solve(rt + numbers[pos], pos + 1, numbers, totals);
        recursively_solve(rt * numbers[pos], pos + 1, numbers, totals);
    }
}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-7/real-input.txt");

    long total = 0;

    auto entries = parse_input(input);
    
    auto counter = 0;

    for(auto entry: entries) {
        set<long> totals;
        recursively_solve(entry.numbers[0], 1, entry.numbers, totals);
        if(totals.find(entry.total) != totals.end()) {
            total+= entry.total;
        }
    }

    cout << "Part one: " << total << endl;

}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-7/test-input.txt");

    auto total = 0;

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}