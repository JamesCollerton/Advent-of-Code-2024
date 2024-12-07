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

void print(vector<string> input) {
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input.size(); j++) {
            cout << input[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void fill_up_directions(const Position &position, const vector<string> &input, vector<vector<set<Direction>>> &seen_directions) {

    if(position.direction == UP || position.direction == DOWN) {
        // Fill up
        int v = position.v;
        int h = position.h;

        while(v >= 0 && v < seen_directions.size() && input[v][h] != '#') {
            // cout << "Filling v: " << v << ", h: " << h << ", d: " << position.direction.name << endl;
            seen_directions[v][h].insert(position.direction);
            v++;
        }

        // Fill down
        v = position.v;

        while(v >= 0 && v < seen_directions.size() && input[v][h] != '#') {
            // cout << "Filling v: " << v << ", h: " << h << ", d: " << position.direction.name << endl;
            seen_directions[v][h].insert(position.direction);
            v--;
        }
    } else {
        // Fill left
        int v = position.v;
        int h = position.h;

        while(h >= 0 && h < seen_directions[v].size() && input[v][h] != '#') {
            // cout << "Filling v: " << v << ", h: " << h << ", d: " << position.direction.name << endl;
            seen_directions[v][h].insert(position.direction);
            h--;
        }

        // Fill right
        h = position.h;

        while(h >= 0 && h < seen_directions[v].size() && input[v][h] != '#') {
            // cout << "Filling v: " << v << ", h: " << h << ", d: " << position.direction.name << endl;
            seen_directions[v][h].insert(position.direction);
            h++;
        }
    }

}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-6/real-input.txt");

    auto total = 0;

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

    input[position.v][position.h] = 'X';

    // While in grid
    while(position.v > 0 && position.v < input.size() && position.h > 0 && position.h < input[0].size()) {
        
        // print(input);

        int new_v = position.v + position.direction.v;
        int new_h = position.h + position.direction.h;

        // If next move is blocked, we need to turn
        if(input[new_v][new_h] == '#') {
            position.direction = *position.direction.next;
        } else {

            // If we're on the block, make a note of the direction we were going in.
            // seen_directions[position.v][position.h].insert(position.direction);

            fill_up_directions(position, input, seen_directions);

            set<Direction> poss_next_directions = seen_directions[position.v][position.h];

            // If we're on a square where by turning right we can mimic an already
            // visited square, we can create a loop.
            if(poss_next_directions.find(*position.direction.next) != poss_next_directions.end()) {
                // cout << "----------------------------" << endl;
                // cout << "Next directions: ";
                // for (Direction const& direction : poss_next_directions) {
                //     cout << direction.name << ' ';
                // }
                // cout << endl;
                // cout << "v: " << position.v <<  ", h: " << position.h << ", d:" << position.direction.name << ", n: " << position.direction.next->name  << endl;
                // cout << "----------------------------" << endl;
                // cout << endl;
                total++;
            }

            // If current block is not visited
            if(input[position.v][position.h] == '.') {

                // Mark this block as used
                input[position.v][position.h] = 'X';

            // If we have been to this square then check if our next direction is in the list 
            // of previously visited directions.
            } else {
                // set<Direction> poss_next_directions = seen_directions[position.v][position.h];

                // If we're on a square where by turning right we can mimic an already
                // visited square, we can create a loop.
                // if(poss_next_directions.find(*position.direction.next) != poss_next_directions.end()) {
                //     // cout << "----------------------------" << endl;
                //     // cout << "Next directions: ";
                //     // for (Direction const& direction : poss_next_directions) {
                //     //     cout << direction.name << ' ';
                //     // }
                //     // cout << endl;
                //     // cout << "v: " << position.v <<  ", h: " << position.h << ", d:" << position.direction.name << ", n: " << position.direction.next->name  << endl;
                //     // cout << "----------------------------" << endl;
                //     // cout << endl;
                //     total++;
                // }
            }
            // Move on
            position.v = new_v;
            position.h = new_h;
        }
    }

    cout << "Part two: " << total << endl;

}

// Expected:
//      6, 4
//      6, 6
//      7, 6

int main() {

    set_up_directions();

    part_one();
    part_two();

    return 0;
}