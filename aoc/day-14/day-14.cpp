#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include "../io/io.h"

using namespace std;

struct Coord {
    long x;
    long y;
};

struct Position {
    Coord location;
    Coord velocity;
};

long find_last_number(string s) {
    size_t last_index = s.find_last_not_of("-0123456789");
    return stol(s.substr(last_index + 1));
}

long find_first_number(string s) {
    size_t first_index = s.find_first_of("-0123456789");
    return stol(s.substr(first_index));
}

// They never move negatively
vector<Position> parse_input(vector<string> input) {

    vector<Position> result;
    for(int i = 0; i < input.size(); i++) {
        auto s = input[i];
        
        auto left = s.substr(0, s.find(' '));
        auto right = s.substr(s.find(' ') + 1);

        Coord location = {.x = find_first_number(left), .y = find_last_number(left)};
        Coord velocity = {.x = find_first_number(right), .y = find_last_number(right)};
        result.push_back({.location = location, .velocity = velocity});
    }

    return result;
}

void print(Position p) {
    cout << "l.x: " << p.location.x << ", l.y: " << p.location.y << endl;
    cout << "v.x: " << p.velocity.x << ", v.y: " << p.velocity.y << endl;
    cout << endl;
}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-14/real-input.txt");
    auto height = 103;
    auto width = 101;
    auto turns = 100;

    auto lower_x_bound = width / 2 - 1;
    auto lower_y_bound = height / 2 - 1;

    auto upper_x_bound = width / 2 + 1;
    auto upper_y_bound = height / 2 + 1;

    long quadrant_1 = 0;
    long quadrant_2 = 0;
    long quadrant_3 = 0;
    long quadrant_4 = 0;

    vector<Position> positions = parse_input(input);
    vector<Coord> coords;

    for(auto p: positions) {

        // Count for negative case
        long final_x;
        long final_y;

        long unadjusted_x = (p.location.x + turns * p.velocity.x) % width;
        long unadjusted_y = (p.location.y + turns * p.velocity.y) % height;

        if(unadjusted_x >= 0) { 
            final_x = unadjusted_x;
        } else {
            final_x = (width) + (unadjusted_x);
        }

        if(unadjusted_y >= 0) {
            final_y = unadjusted_y;
        } else {
            final_y = (height) + (unadjusted_y);
        }


        if(final_x <= lower_x_bound && final_y <= lower_y_bound) {
            quadrant_1++;
        } else if(final_x >= upper_x_bound && final_y <= lower_y_bound) {
            quadrant_2++;
        } else if(final_x <= lower_x_bound && final_y >= upper_y_bound) {
            quadrant_3++;
        } else if(final_x >= upper_x_bound && final_y >= upper_y_bound) {
            quadrant_4++;
        }

    }

    cout << "Part one: " << quadrant_1 * quadrant_2 * quadrant_3 * quadrant_4 << endl;

}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-13/real-input.txt");

    long long total = 0;

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}