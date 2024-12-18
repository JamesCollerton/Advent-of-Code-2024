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

long part_one_total = LLONG_MAX;

void recursively_find_total(const Direction &direction, const vector<string> &input, vector<vector<bool>> &seen, int v, int h, long running_total) {
    
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

    if(v >= 0 && v < input.size() && h >= 0 && h < input[v].size() && input[v][h] != '#' && !seen[v][h]) {
        if(input[v][h] == 'E') {
            part_one_total = min(part_one_total, running_total);
            cout << part_one_total << endl;
        } else {
            seen[v][h] = true;
            if(direction == NORTH) {
                recursively_find_total(NORTH, input, seen, v - 1, h, running_total + 1);
                recursively_find_total(SOUTH, input, seen, v + 1, h, running_total + 2001);
                recursively_find_total(EAST, input, seen, v, h + 1, running_total + 1001);
                recursively_find_total(WEST, input, seen, v, h - 1, running_total + 1001);
            } else if(direction == SOUTH) {
                recursively_find_total(NORTH, input, seen, v - 1, h, running_total + 2001);
                recursively_find_total(SOUTH, input, seen, v + 1, h, running_total + 1);
                recursively_find_total(EAST, input, seen, v, h + 1, running_total + 1001);
                recursively_find_total(WEST, input, seen, v, h - 1, running_total + 1001);
            } else if(direction == EAST) {
                recursively_find_total(NORTH, input, seen, v - 1, h, running_total + 1001);
                recursively_find_total(SOUTH, input, seen, v + 1, h, running_total + 1001);
                recursively_find_total(EAST, input, seen, v, h + 1, running_total + 1);
                recursively_find_total(WEST, input, seen, v, h - 1, running_total + 2001);
            // West
            } else {
                recursively_find_total(NORTH, input, seen, v - 1, h, running_total + 1001);
                recursively_find_total(SOUTH, input, seen, v + 1, h, running_total + 1001);
                recursively_find_total(EAST, input, seen, v, h + 1, running_total + 2001);
                recursively_find_total(WEST, input, seen, v, h - 1, running_total + 1);
            }
            seen[v][h] = false;
        }
    }
}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-16/real-input.txt");

    vector<vector<bool>> seen;

    // Find start and initialise array of seen spaces
    int v, h;
    for(int i = 0; i < input.size(); i++) {
        vector<bool> row;
        for(int j = 0; j < input[i].size(); j++) {
            row.push_back(false);
            if(input[i][j] == 'S') {
                v = i;
                h = j;   
            }
        }
        seen.push_back(row);
    }

    recursively_find_total(EAST, input, seen, v, h, 0);

    cout << "Part one: " << part_one_total << endl;

}

struct State {
    int v;
    int h;
    char c;
};

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