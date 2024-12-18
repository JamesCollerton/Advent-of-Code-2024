#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <chrono>
#include <thread>
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

    vector<string> grid;

    long total = 0;

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}