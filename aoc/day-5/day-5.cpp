#include <iostream>
#include <map>
#include <set>
#include <sstream>
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

bool isLineValid(map<int, set<int>> key_to_afters_map, vector<int> line, bool print) {

    bool result = true;

    for(int i = line.size() - 1; i > 0; i--) {
        set<int> banned_nums = key_to_afters_map[line[i]];
        for(int j = 0; j < i; j++) {
            if(banned_nums.count(line[j]) > 0) {
                if(print) {
                    cout << line[j] << " " << endl;
                }
                result = false;
            }
        }
    }

    return result;
}

bool isLineValid(map<int, set<int>> key_to_afters_map, vector<int> line) {
    isLineValid(key_to_afters_map, line, false);
}

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

vector<int> orderLine(map<int, set<int>> key_to_afters_map, vector<int> line) {

    vector<int> reordered_line = line;
    map<int, int> num_to_position;

    for(int i = 0; i < line.size(); i++) {
        num_to_position[line[i]] = i;
    }

    // printMap(key_to_afters_map);

    int i = 0;

    for(auto it = key_to_afters_map.cbegin(); it != key_to_afters_map.cend(); ++it) {

        // cout << "Loop " << i << endl;
        
        // printLine(reordered_line);
        // printMap(num_to_position);

        auto curr_num = it->first;
        auto to_swap = it->second;

        if(num_to_position.find(curr_num) != num_to_position.end()) {

            // cout << "Current number: " << curr_num << " position: " << num_to_position[curr_num] << endl;

            // printMap(num_to_position);

            for(auto swap_num = to_swap.cbegin(); swap_num != to_swap.cend(); ++swap_num) {

                if(num_to_position.find(*swap_num) != num_to_position.end()) {

                    cout << endl;
                    printMap(num_to_position);

                    printLine(reordered_line);
                    cout << "Current number: " << curr_num << " position: " << num_to_position[curr_num] << endl;
                    cout << "Number to swap: " << *swap_num << " position: " << num_to_position[*swap_num] << endl;
                    cout << endl;
                }

                if(num_to_position.find(*swap_num) != num_to_position.end() && num_to_position[*swap_num] < num_to_position[curr_num]) {

                    // cout << "Number to swap: " << *swap_num << " position: " << num_to_position[*swap_num] << endl;

                    reordered_line.insert(reordered_line.begin() + num_to_position[*swap_num], curr_num);

                    // printLine(reordered_line);

                    // Move everything along 1

                    reordered_line.erase(reordered_line.begin() + num_to_position[curr_num] + 1);

                    // printLine(reordered_line);
                    
                    for(int i = num_to_position[*swap_num]; i < line.size(); i++) {
                        num_to_position[line[i]] = num_to_position[line[i]] + 1;
                    }

                    // num_to_position[*swap_num] = num_to_position[*swap_num] + 1;
                    num_to_position[curr_num] = num_to_position[*swap_num] - 1;
                }
            }

        }

        i++;
    }

    return reordered_line;
}

void partTwo(ParsedInput parsed_input) {

    // printMap(parsed_input.key_to_afters_map);

    int total = 0;

    vector<vector<int>> lines = {{26, 25, 89, 49, 58, 24, 37}};

    // for(auto line: parsed_input.page_orders) {
    for(auto line: lines) {
        if(!isLineValid(parsed_input.key_to_afters_map, line)) {
            auto ordered_line = orderLine(parsed_input.key_to_afters_map, line);

            if(!isLineValid(parsed_input.key_to_afters_map, ordered_line, true)) {
                cout << "Invalid line" << endl;
                printLine(line);
                printLine(ordered_line);
                cout << endl;
            }

            total += ordered_line[ordered_line.size() / 2];
        }
    }
    // }

    cout << "Part two: " << total << endl;

}

int main() {

    const auto io = IO();
    const auto input = io.readFile("./io/day-5/real-input.txt");

    ParsedInput parsed_input = parseInput(input);

    // partOne(parsed_input);
    // printMap(parsed_input.key_to_afters_map);
    partTwo(parsed_input);

    return 0;
}

// 61 96 89 91 33