#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../io/io.h"

using namespace std;

struct Details {
    long area;
    long perimiter;
};

bool is_valid(const vector<string> &input, int v, int h, char c) {
    return v >= 0 && v < input.size() && h >= 0 && h < input[v].size() && input[v][h] == c;
}

Details recursive_area_perimiter(vector<vector<bool>> &seen, const vector<string> &input, int v, int h, char c) {
    
    seen[v][h] = true;
    
    auto perimiter = 4;
    auto area = 1;
    // For each direction, if there's an adjoining square substract one
    // from the perimiter. If we've not visited it then go to it.
    // int directions[4][2] = {{-1, 0}, (1, 0), {0, 1}, {0, -1}};
    vector<vector<int>> directions;
    directions.push_back({-1, 0});
    directions.push_back({1, 0});
    directions.push_back({0, 1});
    directions.push_back({0, -1});

    // Look in each direction
    for(int i = 0; i < directions.size(); i++) {
        int v_incr = directions[i][0];
        int h_incr = directions[i][1];
        if(is_valid(input, v + v_incr, h + h_incr, c)) {
            perimiter--;
            if(!seen[v + v_incr][h + h_incr]) {

                // If it's the same type and we've not visited it then
                // go and explore
                auto result = recursive_area_perimiter(seen, input, v + v_incr, h + h_incr, c);
                perimiter += result.perimiter;
                area += result.area;
            }
        }
    }

    return {.area = area, .perimiter = perimiter};

}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-12/real-input.txt");

    long total = 0;

    // Make an array so we can mark off seen squares
    vector<vector<bool>> seen;
    for(int i = 0; i < input.size(); i++) {
        vector<bool> row;
        for(int j = 0; j < input[i].size(); j++) {
            row.push_back(false);
        }
        seen.push_back(row);
    }

    // Map of types to area and perimiters
    map<char, Details> map;

    // For each unseen node we want to recursively
    // find the area and perimiter for the same nodes
    // surrounding it.
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size(); j++) {

            // If we've not seen it, recursively find
            // all the information surrounding it
            if(!seen[i][j]) {

                // We know this is an area worth exploring
                char c = input[i][j];
                auto result = recursive_area_perimiter(seen, input, i, j, c);

                cout << "c: " << c << ", a: " << result.area << ", p: " << result.perimiter << endl;

                total += result.area * result.perimiter;

                // If we already have a total for this type then
                // add to it
                // if(map.find(c) != map.end()) {
                //     map[c] = {.area = map[c].area + result.area, .perimiter = map[c].perimiter + result.perimiter};
                // } else {
                //     map[c] = result;
                // }
            }
        }
    }

    // Now we have a map of plant type to area/ perimiter
    // we can go through and sum them all.
    // for (auto const& [key, details]: map) {
    //     total += details.area * details.perimiter;
    // }

    cout << "Part one: " << total << endl;

}

// Simplified function for just finding the area for a type
int recursive_area(vector<vector<bool>> &seen, const vector<string> &input, int v, int h, char c) {
    
    seen[v][h] = true;
    
    auto area = 1;

    vector<vector<int>> directions;
    directions.push_back({-1, 0});
    directions.push_back({1, 0});
    directions.push_back({0, 1});
    directions.push_back({0, -1});

    // For each direction, if it's valid, look that
    // way then add to the area
    for(int i = 0; i < directions.size(); i++) {
        int v_incr = directions[i][0];
        int h_incr = directions[i][1];
        if(is_valid(input, v + v_incr, h + h_incr, c)) {
            if(!seen[v + v_incr][h + h_incr]) {
                area += recursive_area(seen, input, v + v_incr, h + h_incr, c);
            }
        }
    }

    return area;

}

// Corner pieces have:
//  More than one side on the edge.

// A A
// A A

// C
// C C
//   C

// Simplified function for finding the number of sides. The idea is
// that you are going in one direction, never going to a state where
// it's on the inside. We try going in one direction, if we can't go
// in that direction then we must have found a side.

// We don't stop walking until we end up at the start, but we can revisit
// the same square multiple times.
int recursive_sides(vector<vector<bool>> &seen, const vector<string> &input, int v, int h, char c) {
    
    seen[v][h] = true;
    
    auto area = 1;

    vector<vector<int>> directions;
    directions.push_back({-1, 0});
    directions.push_back({1, 0});
    directions.push_back({0, 1});
    directions.push_back({0, -1});

    // For each direction, if it's valid, look that
    // way then add to the area
    for(int i = 0; i < directions.size(); i++) {
        int v_incr = directions[i][0];
        int h_incr = directions[i][1];
        if(is_valid(input, v + v_incr, h + h_incr, c)) {
            if(!seen[v + v_incr][h + h_incr]) {
                area += recursive_area(seen, input, v + v_incr, h + h_incr, c);
            }
        }
    }

    return area;

}

void part_two() {

 const auto io = IO();
    auto input = io.readFile("./io/day-12/test-input.txt");

    long total = 0;

    // Make an array so we can mark off seen squares
    vector<vector<bool>> seen;
    for(int i = 0; i < input.size(); i++) {
        vector<bool> row;
        for(int j = 0; j < input[i].size(); j++) {
            row.push_back(false);
        }
        seen.push_back(row);
    }

    // For each unseen node we want to recursively first
    // find the area, then try and walk round the outside
    // and find the number of sides
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size(); j++) {

            if(!seen[i][j]) {

                char c = input[i][j];

                // We need to make one copy of the seen
                // array for doing the sides. The area
                // will cover these for the next iteration
                auto sides_seen = seen;
                auto area = recursive_area(seen, input, i, j, c);

                // We know at the start we must have
                auto sides = recursive_sides(sides_seen, input, i, j, c);

                total += area * sides;
            }
        }
    }

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}