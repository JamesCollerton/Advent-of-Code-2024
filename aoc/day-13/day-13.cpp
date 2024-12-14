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

int bfs_find_min_tokens(Puzzle puzzle) {

    long min_tokens = LLONG_MAX;
    queue<State> queue;

    queue.push({0, 0, 0});
    int level = 0;

    while(level < 100 && queue.size() != 0) {
        int size = queue.size();
        for(int i = 0; i < size; i++) {
            State state = queue.front();
            queue.pop();

            // Only bother moving if we're going to
            // improve on the current state
            if(state.tokens < min_tokens) {
                if(state.x == puzzle.p.x && state.y == puzzle.p.y) {
                    min_tokens = min(state.tokens, min_tokens);
                } else {
                    // Make A move
                    queue.push({state.x + puzzle.a.x, state.y + puzzle.a.y, state.tokens + 3});
                    // Make B move
                    queue.push({state.x + puzzle.b.x, state.y + puzzle.b.y, state.tokens + 1});
                }
            }
        }
        cout << "Level: " << level << endl;
        level++;
    }

}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-13/test-input.txt");

    long total = 0;

    vector<Puzzle> puzzles = parse_input(input);
    for(auto p: puzzles) {
        // print(p);
        total += bfs_find_min_tokens(p);
    }

    cout << "Part one: " << total << endl;

}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-13/test-input.txt");

    long total = 0;

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}