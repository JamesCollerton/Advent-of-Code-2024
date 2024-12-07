#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../io/io.h"

using namespace std;

struct Direction {
    int v;
    int h;
    string name;
    Direction *next;

    bool operator<(const Direction& rhs) const {
        return name < rhs.name;
    }

    bool operator==(const Direction& rhs) const {
        return name == rhs.name;
    }
};

Direction UP = {-1, 0, "UP"};
Direction RIGHT = {0, 1, "RIGHT"};
Direction DOWN = {1, 0, "DOWN"};
Direction LEFT = {0, -1, "LEFT"};

struct Position {
    int v;
    int h;
    Direction direction;
};

void set_up_directions() {
    UP.next = &RIGHT;
    RIGHT.next = &DOWN;
    DOWN.next = &LEFT;
    LEFT.next = &UP;
}

Position find_initial_position(const vector<string> &input) {
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size(); j++) {
            char c = input[i][j];
            // Assume no down arrow
            if(c == '^') {
                return {i, j, UP};
            } else if(c == '>') {
                return {i, j, RIGHT};
            } else if(c == '<') {
                return {i, j, LEFT};
            }
        }
    }
}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-6/real-input.txt");

    auto total = 0;

    // Find initial position and direction
    auto position = find_initial_position(input);

    // While in grid
    while(position.v > 0 && position.v < input.size() && position.h > 0 && position.h < input[0].size()) {
        int new_v = position.v + position.direction.v;
        int new_h = position.h + position.direction.h;
        // If next move is blocked
        if(input[new_v][new_h] == '#') {
            position.direction = *position.direction.next;
        } else {
            // If current block is not used
            if(input[position.v][position.h] == '.') {
                input[position.v][position.h] = 'X';
                total++;
            }
            // Move on
            position.v = new_v;
            position.h = new_h;
        }
    }

    cout << "Part one: " << total + 1 << endl;

}

bool loop_exists(vector<string> &input) {

    // Find initial position and direction
    auto position = find_initial_position(input);

    // Make empty grid of visited directions
    vector<vector<set<Direction>>> seen_directions;

    for(int i = 0; i < input.size(); i++) {
        vector<set<Direction>> row;
        for(int j = 0; j < input[i].size(); j++) {
            set<Direction> directions;
            row.push_back(directions);
        }
        seen_directions.push_back(row);
    }

    // While in grid
    while(position.v >= 0 && position.v < input.size() && position.h >= 0 && position.h < input[0].size()) {

        // Check to see if we've been on this square, and in this direction
        auto seen_direction_set = seen_directions[position.v][position.h];

        if(input[position.v][position.h] == 'X' && seen_direction_set.find(position.direction) != seen_direction_set.end()) {
            return true;
        }

        // Mark this square as visited in this direction
        input[position.v][position.h] = 'X';
        seen_directions[position.v][position.h].insert(position.direction);

        // Calculate new positions
        int new_v = position.v + position.direction.v;
        int new_h = position.h + position.direction.h;
        
        // If we're stepping off the board, then there's no loop
        if(!(new_v >= 0 && new_v < input.size() && new_h >= 0 && new_h < input[0].size())) {
            return false;
        }

        // If next move is blocked we need to change direction
        if(input[new_v][new_h] == '#') {
            position.direction = *position.direction.next;

        // Otherwise move forward
        } else {
            position.v = new_v;
            position.h = new_h;
        }
    }

    return false;
}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-6/real-input.txt");

    auto total = 0;

    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size(); j++) {
            auto input_copy = input;
            if(input_copy[i][j] == '.') {
                input_copy[i][j] = '#';
                if(loop_exists(input_copy)) {
                    total++;
                }
            }
        }
    }


    cout << "Part two: " << total << endl;

}

int main() {

    set_up_directions();

    part_one();
    part_two();

    return 0;
}