#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
#include <thread>
#include <tuple>
#include "../io/io.h"

using namespace std;

enum Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

struct State {
    int v;
    int h;
    long running_total;
    Direction direction;
    vector<vector<int>> coords;
    bool operator<(const State& rhs) const {
        return running_total > rhs.running_total;
    }
};

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-16/real-input.txt");

    vector<vector<long>> totals;

    // Find start and initialise array of seen spaces
    int v, h;
    for(int i = 0; i < input.size(); i++) {
        vector<long> row;
        for(int j = 0; j < input[i].size(); j++) {
            row.push_back(LLONG_MAX);
            if(input[i][j] == 'S') {
                v = i;
                h = j;   
            }
        }
        totals.push_back(row);
    }

    long total = LLONG_MAX;
    priority_queue<State> to_visit;
    to_visit.push(State{.v = v, .h = h, .running_total = 0, .direction = EAST});

    while(!to_visit.empty()) {
        auto state = to_visit.top();
        to_visit.pop();

        cout << to_visit.size() << endl;
        cout << total << endl;
        cout << "Running total " << state.running_total << endl;

        // cout << state.running_total << endl;
        // cout << totals[state.v][state.h] << endl;
        // cout << to_visit.size() << endl;

        // for(int i = 0; i < input.size(); i++) {
        //     for(int j = 0; j < input[i].size(); j++) {
        //         if(!seen[i][j]) {
        //             cout << input[i][j];
        //         } else {
        //             cout << 'X';
        //         }
        //     }
        //     cout << endl;
        // }

        // cout << "v: " << state.v << ", h: " << state.h << endl;

        if(state.v >= 0 && state.v < input.size() && state.h >= 0 && state.h < input[state.v].size() && input[state.v][state.h] != '#' && totals[state.v][state.h] > state.running_total) {
            if(input[state.v][state.h] == 'E') {
                total = min(total, state.running_total);
            } else {
                totals[state.v][state.h] = state.running_total;
                if(state.direction == NORTH) {
                    to_visit.push({.v = state.v - 1, .h = state.h, .running_total = state.running_total + 1, .direction = NORTH});
                    to_visit.push({.v = state.v + 1, .h = state.h, .running_total = state.running_total + 2001, .direction = SOUTH});
                    to_visit.push({.v = state.v, .h = state.h + 1, .running_total = state.running_total + 1001, .direction = EAST});
                    to_visit.push({.v = state.v, .h = state.h - 1, .running_total = state.running_total + 1001, .direction = WEST});
                } else if(state.direction == SOUTH) {
                    to_visit.push({.v = state.v - 1, .h = state.h, .running_total = state.running_total + 2001, .direction = NORTH});
                    to_visit.push({.v = state.v + 1, .h = state.h, .running_total = state.running_total + 1, .direction = SOUTH});
                    to_visit.push({.v = state.v, .h = state.h + 1, .running_total = state.running_total + 1001, .direction = EAST});
                    to_visit.push({.v = state.v, .h = state.h - 1, .running_total = state.running_total + 1001, .direction = WEST});
                } else if(state.direction == EAST) {
                    to_visit.push({.v = state.v - 1, .h = state.h, .running_total = state.running_total + 1001, .direction = NORTH});
                    to_visit.push({.v = state.v + 1, .h = state.h, .running_total = state.running_total + 1001, .direction = SOUTH});
                    to_visit.push({.v = state.v, .h = state.h + 1, .running_total = state.running_total + 1, .direction = EAST});
                    to_visit.push({.v = state.v, .h = state.h - 1, .running_total = state.running_total + 2001, .direction = WEST});
                // West
                } else {
                    to_visit.push({.v = state.v - 1, .h = state.h, .running_total = state.running_total + 1001, .direction = NORTH});
                    to_visit.push({.v = state.v + 1, .h = state.h, .running_total = state.running_total + 1001, .direction = SOUTH});
                    to_visit.push({.v = state.v, .h = state.h + 1, .running_total = state.running_total + 2001, .direction = EAST});
                    to_visit.push({.v = state.v, .h = state.h - 1, .running_total = state.running_total + 1, .direction = WEST});
                }
            }
        }
    }

    cout << "Part one: " << total << endl;

}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-16/test-input-1.txt");

    vector<vector<long>> totals;

    // Find start and initialise array of seen spaces
    int v, h;
    for(int i = 0; i < input.size(); i++) {
        vector<long> row;
        for(int j = 0; j < input[i].size(); j++) {
            row.push_back(LLONG_MAX);
            if(input[i][j] == 'S') {
                v = i;
                h = j;   
            }
        }
        totals.push_back(row);
    }

    long total = LLONG_MAX;
    priority_queue<State> to_visit;
    map<long, vector<vector<int>>> res_map;
    to_visit.push(State{.v = v, .h = h, .running_total = 0, .direction = EAST, .coords = vector<vector<int>>()});

    while(!to_visit.empty()) {
        auto state = to_visit.top();
        to_visit.pop();

        cout << "Running total " << state.running_total << endl;

        bool seen_in_run = false;
        for(int i = 0; i < state.coords.size(); i++) {
            if(state.coords[i][0] == state.v && state.coords[i][1] == state.h) {
                seen_in_run = true;
            }
        }

        // auto curr_grid = input;
        // for(int i = 0; i < state.coords.size(); i++) {
        //     curr_grid[state.coords[i][0]][state.coords[i][1]] = 'X';
        // }
        // for(int i = 0; i < curr_grid.size(); i++) {
        //     for(int j = 0; j < curr_grid[j].size(); j++) {
        //         cout << curr_grid[i][j];
        //     }
        //     cout << endl;
        // }

        // for(int i = 0; i < 100; i++) {
        //     cout << endl;
        // }


        // for(int i = 0; i < input.size(); i++) {
        //     for(int j = 0; j < input[i].size(); j++) {
        //         if(!seen[i][j]) {
        //             cout << input[i][j];
        //         } else {
        //             cout << 'X';
        //         }
        //     }
        //     cout << endl;
        // }

        if(state.v >= 0 && state.v < input.size() && state.h >= 0 && state.h < input[state.v].size() && input[state.v][state.h] != '#' && totals[state.v][state.h] >= state.running_total) {
            if(input[state.v][state.h] == 'E') {
                if(res_map.find(state.running_total) != res_map.end()) {
                    for(int i = 0; i < state.coords.size(); i++) {
                        res_map.find(state.running_total)->second.push_back(state.coords[i]);
                    }
                } else {
                    res_map[state.running_total] = state.coords;
                }
                if(total == state.running_total) {
                    cout << "New route!" << endl;
                }
                total = min(total, state.running_total);
            } else {
                totals[state.v][state.h] = state.running_total;
                auto coords = state.coords;
                coords.push_back({state.v, state.h});
                if(state.direction == NORTH) {
                    to_visit.push({.v = state.v - 1, .h = state.h, .running_total = state.running_total + 1, .direction = NORTH, .coords = coords});
                    to_visit.push({.v = state.v + 1, .h = state.h, .running_total = state.running_total + 2001, .direction = SOUTH, .coords = coords});
                    to_visit.push({.v = state.v, .h = state.h + 1, .running_total = state.running_total + 1001, .direction = EAST, .coords = coords});
                    to_visit.push({.v = state.v, .h = state.h - 1, .running_total = state.running_total + 1001, .direction = WEST, .coords = coords});
                } else if(state.direction == SOUTH) {
                    to_visit.push({.v = state.v - 1, .h = state.h, .running_total = state.running_total + 2001, .direction = NORTH, .coords = coords});
                    to_visit.push({.v = state.v + 1, .h = state.h, .running_total = state.running_total + 1, .direction = SOUTH, .coords = coords});
                    to_visit.push({.v = state.v, .h = state.h + 1, .running_total = state.running_total + 1001, .direction = EAST, .coords = coords});
                    to_visit.push({.v = state.v, .h = state.h - 1, .running_total = state.running_total + 1001, .direction = WEST, .coords = coords});
                } else if(state.direction == EAST) {
                    to_visit.push({.v = state.v - 1, .h = state.h, .running_total = state.running_total + 1001, .direction = NORTH, .coords = coords});
                    to_visit.push({.v = state.v + 1, .h = state.h, .running_total = state.running_total + 1001, .direction = SOUTH, .coords = coords});
                    to_visit.push({.v = state.v, .h = state.h + 1, .running_total = state.running_total + 1, .direction = EAST, .coords = coords});
                    to_visit.push({.v = state.v, .h = state.h - 1, .running_total = state.running_total + 2001, .direction = WEST, .coords = coords});
                // West
                } else {
                    to_visit.push({.v = state.v - 1, .h = state.h, .running_total = state.running_total + 1001, .direction = NORTH, .coords = coords});
                    to_visit.push({.v = state.v + 1, .h = state.h, .running_total = state.running_total + 1001, .direction = SOUTH, .coords = coords});
                    to_visit.push({.v = state.v, .h = state.h + 1, .running_total = state.running_total + 2001, .direction = EAST, .coords = coords});
                    to_visit.push({.v = state.v, .h = state.h - 1, .running_total = state.running_total + 1, .direction = WEST, .coords = coords});
                }
                // totals[state.v][state.h] = state.running_total;
            }
        }
    }

    for(int i = 0; i < res_map[total].size(); i++) {
        input[res_map[total][i][0]][res_map[total][i][1]] = 'O';
    }

    long squares = 0;

    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size(); j++) {
            cout << input[i][j];
            if(input[i][j] == 'O') {
                squares++;
            }
        }
        cout << endl;
    }

    cout << "Part two: " << squares + 1 << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}