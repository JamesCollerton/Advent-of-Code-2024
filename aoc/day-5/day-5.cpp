#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../io/io.h"

using namespace std;

struct ParsedInput {
    map<int, set<int>> key_to_afters_map;
    vector<vector<int>> page_orders;
};

ParsedInput parseInput(const vector<string> &input) {

    map<int, set<int>> key_to_afters_map;
    int pos = 0;

    while(input[pos].find('|') != std::string::npos) {
        const auto line = input[pos];

        const auto left = stoi(line.substr(0, line.find('|')));
        const auto right = stoi(line.substr(line.find('|') + 1));

        if(key_to_afters_map.count(left) > 0) {
            key_to_afters_map[left].insert(right);
        } else {
            key_to_afters_map[left] = set<int>{right};
        }
        pos++;
    }

    // Skip blank line
    pos++;

    vector<vector<int>> page_orders;

    while(pos < input.size()) {
        stringstream ss(input[pos]);
        vector<int> num_vec;
        string temp_s;

        while(getline(ss, temp_s, ',')) {
            num_vec.push_back(stoi(temp_s));
        }

        page_orders.emplace_back(num_vec);
        pos++;   
    }

    return {
        key_to_afters_map,
        page_orders
    };
}

bool isLineValid(const map<int, set<int>> &key_to_afters_map, const vector<int> &line) {

    for(int i = line.size() - 1; i > 0; i--) {
        const set<int> banned_nums = key_to_afters_map.at(line[i]);
        for(int j = 0; j < i; j++) {
            if(banned_nums.count(line[j]) > 0) {
                return false;
            }
        }
    }

    return true;
}

void partOne(const ParsedInput &parsed_input) {

    auto total = 0;

    for(auto line: parsed_input.page_orders) {
        if(isLineValid(parsed_input.key_to_afters_map, line)) {
            total += line[line.size() / 2];
        }
    }

    cout << "Part one: " << total << endl;

}

vector<int> orderLine(const map<int, set<int>> &key_to_afters_map, const vector<int> &line) {

    vector<int> reordered_line = line;

    for(int i = 0; i < line.size(); i++) {

        auto item = line[i];

        if(key_to_afters_map.find(item) != key_to_afters_map.end()) {

            auto afters = key_to_afters_map.at(item);
            auto item_idx = find(reordered_line.begin(), reordered_line.end(), item) - reordered_line.begin();

            for(int i = 0; i < item_idx; i++) {
                if(afters.find(reordered_line[i]) != afters.end()) {
                    reordered_line.insert(reordered_line.begin() + i, item);
                    reordered_line.erase(reordered_line.begin() + item_idx + 1);
                    break;
                }
            }

        }

    }

    return reordered_line;

}

void partTwo(const ParsedInput &parsed_input) {

    int total = 0;

    for(auto line: parsed_input.page_orders) {
        if(!isLineValid(parsed_input.key_to_afters_map, line)) {
            const auto ordered_line = orderLine(parsed_input.key_to_afters_map, line);
            total += ordered_line[ordered_line.size() / 2];
        }
    }

    cout << "Part two: " << total << endl;

}

int main() {

    const auto io = IO();
    const auto input = io.readFile("./io/day-5/real-input.txt");

    ParsedInput parsed_input = parseInput(input);

    partOne(parsed_input);
    partTwo(parsed_input);

    return 0;
}