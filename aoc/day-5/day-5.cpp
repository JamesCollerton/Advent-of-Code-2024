#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../io/io.h"

using namespace std;

// Create a map:
//  Key - Number 
//  Value - A set of all numbers that can only come after a number

// From the end, move backwards

struct ParsedInput {
    map<int, set<int>> key_to_afters_map;
    vector<vector<int>> page_orders;
};

void printMap(map<int, set<int>> key_to_afters_map) {
    for(auto it = key_to_afters_map.cbegin(); it != key_to_afters_map.cend(); ++it) {
        cout << to_string(it->first) << ": ";
        for(auto in_it = it->second.cbegin(); in_it != it->second.cend(); ++in_it) {
            cout << to_string(*in_it) << " ";
        }
        cout << endl;
    }
}

void printPageOrders(vector<vector<int>> page_orders) {
    for(int i = 0; i < page_orders.size(); i++) {
        for(int j = 0; j < page_orders[i].size(); j++) {
            cout << to_string(page_orders[i][j]) << " ";
        }
        cout << endl;
    }
}

ParsedInput parseInput(vector<string> input) {

    map<int, set<int>> key_to_afters_map;
    int pos = 0;

    while(input[pos].find('|') != std::string::npos) {
        auto line = input[pos];

        auto left = stoi(line.substr(0, line.find('|')));
        auto right = stoi(line.substr(line.find('|') + 1));

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

bool isLineValid(map<int, set<int>> key_to_afters_map, vector<int> line) {

// /    bool result = true;

    for(int i = line.size() - 1; i > 0; i--) {
        set<int> banned_nums = key_to_afters_map[line[i]];
        for(int j = 0; j < i; j++) {
            if(banned_nums.count(line[j]) > 0) {
                return false;
            }
        }
    }

    return true;
}

// bool isLineValid(map<int, set<int>> key_to_afters_map, vector<int> line) {
//     isLineValid(key_to_afters_map, line, false);
// }

void partOne(ParsedInput parsed_input) {

    int total = 0;

    for(auto line: parsed_input.page_orders) {
        if(isLineValid(parsed_input.key_to_afters_map, line)) {
            total += line[line.size() / 2];
        }
    }

    cout << "Part one: " << total << endl;

}

void printLine(vector<int> line) {
    cout << "Line: ";
    for(auto i : line) {
        cout << i << " ";
    }
    cout << endl;
}

void printMap(map<int, int> map) {
    for(auto it = map.cbegin(); it != map.cend(); ++it) {
        cout << to_string(it->first) << ": " << to_string(it->second) << endl;
    }
}

void printSet(set<int> set) {
    cout << "Set ";
    for(auto it = set.cbegin(); it != set.cend(); ++it) {
        cout << to_string(*it) << " ";
    }
    cout << endl;
}

vector<int> orderLine(map<int, set<int>> key_to_afters_map, vector<int> line) {

    vector<int> reordered_line = line;

    for(int i = 0; i < line.size(); i++) {

        auto item = line[i];

        if(key_to_afters_map.find(item) != key_to_afters_map.end()) {

            set<int> afters = key_to_afters_map[item];
            int item_idx = find(reordered_line.begin(), reordered_line.end(), item) - reordered_line.begin();

            for(int i = 0; i < item_idx; i++) {
                if(afters.find(reordered_line[i]) != afters.end()) {
                    reordered_line.insert(reordered_line.begin() + i, item);
                    reordered_line.erase(reordered_line.begin() + item_idx + 1);
                    cout << endl;
                    break;
                }
            }

        }

    }

    return reordered_line;

}

void partTwo(ParsedInput parsed_input) {

    int total = 0;

    for(auto line: parsed_input.page_orders) {
        if(!isLineValid(parsed_input.key_to_afters_map, line)) {
            auto ordered_line = orderLine(parsed_input.key_to_afters_map, line);
            total += ordered_line[ordered_line.size() / 2];
        } else {
            cout << "Valid line";
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

// 61 96 89 91 33