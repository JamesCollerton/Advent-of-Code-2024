#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include "../io/io.h"

using namespace std;

struct Button {
    long x;
    long y;
};

struct Prize {
    long x;
    long y;
};

struct Puzzle {
    Button a;
    Button b;
    Prize p;
};

struct State {
    long x;
    long y;
    long tokens;
};

long find_last_number(string s) {
    size_t last_index = s.find_last_not_of("0123456789");
    return stol(s.substr(last_index + 1));
}

long find_first_number(string s) {
    size_t first_index = s.find_first_of("0123456789");
    return stol(s.substr(first_index));
}

// They never move negatively
vector<Puzzle> parse_input(vector<string> input) {

    vector<Puzzle> result;
    Puzzle puzzle;
    for(int i = 0; i < input.size(); i++) {
        auto s = input[i];
        if(s.find("Button A") != std::string::npos) {
            auto a = Button{ .x = find_first_number(s), .y = find_last_number(s) };
            puzzle.a = a;
        } else if(s.find("Button B") != std::string::npos) {
            auto b = Button{ .x = find_first_number(s), .y = find_last_number(s) };
            puzzle.b = b;
        } else if(s.find("Prize") != std::string::npos) {
            auto p = Prize{ .x = find_first_number(s), .y = find_last_number(s) };
            puzzle.p = p;
            result.push_back(puzzle);
        }
    }

    return result;
}

void print(Puzzle p) {
    cout << "A.x: " << p.a.x << ", A.y: " << p.a.y << endl;
    cout << "B.x: " << p.b.x << ", B.y: " << p.b.y << endl;
    cout << "Prize.x: " << p.p.x << ", Prize.y: " << p.p.y << endl;
    cout << endl;
}

int maths_find_min_tokens(Puzzle puzzle) {

    int p_x = puzzle.p.x;
    int p_y = puzzle.p.y;
    int a_x = puzzle.a.x;
    int a_y = puzzle.a.y;
    int b_x = puzzle.b.x;
    int b_y = puzzle.b.y;
    
    long q_numerator = ((p_y * a_x) - (p_x * a_y));
    long q_denominator = ((a_x * b_y) - (b_x * a_y));

    int q = q_numerator / q_denominator;
    int r = ((p_x - q * b_x) / a_x);

    if((r > 0 && q > 0 && r < 100 && q < 100) && (r * a_x + q * b_x == p_x) && (r * a_x + q * b_x == p_x)) {
        return r * 3 + q * 1;
    } 

    return 0;
}

long long maths_find_min_tokens_2(Puzzle puzzle) {

    long long p_x = puzzle.p.x + 10000000000000;
    long long p_y = puzzle.p.y + 10000000000000;
    long long a_x = puzzle.a.x;
    long long a_y = puzzle.a.y;
    long long b_x = puzzle.b.x;
    long long b_y = puzzle.b.y;
    
    long long q_numerator = ((p_y * a_x) - (p_x * a_y));
    long long q_denominator = ((a_x * b_y) - (b_x * a_y));

    long long q = q_numerator / q_denominator;
    long long r = ((p_x - q * b_x) / a_x);

    if((r >= 0 && q >= 0) && (r * a_x + q * b_x == p_x) && (r * a_y + q * b_y == p_y)) {
        return r * 3 + q * 1;
    } 

    return 0;
}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-13/real-input.txt");

    long total = 0;

    vector<Puzzle> puzzles = parse_input(input);
    for(auto p: puzzles) {
        total += maths_find_min_tokens(p);
    }

    cout << "Part one: " << total << endl;

}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-13/real-input.txt");

    long long total = 0;

    vector<Puzzle> puzzles = parse_input(input);
    for(auto p: puzzles) {
        cout << total << endl;
        total += maths_find_min_tokens_2(p);
    }

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}