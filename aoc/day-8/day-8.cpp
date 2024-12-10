#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../io/io.h"

using namespace std;

struct Coord {
    int v;
    int h;
};

map<char, vector<Coord>> parse_input(const vector<string> &input) {

    map<char, vector<Coord>> nodes;

    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size() ; j++) {
            char c = input[i][j];
            if(c != '.') {
                if(nodes.find(c) != nodes.end()) {
                    nodes.find(c)->second.emplace_back(Coord{i, j});
                } else {
                    nodes[c] = {Coord{i, j}};
                }
            }
        }
    }

    return nodes;
}

void print(const map<char, vector<Coord>> &map) {

    for(auto it = map.cbegin(); it != map.cend(); ++it) {
        cout << it->first << ": ";
        for(auto coord: it->second) {
            cout << "[" << coord.v << "," << coord.h << "] ";
        }
        cout << endl;
    }

}

bool is_valid(int v, int h, vector<string> input) {
    return (v >= 0 && v < input.size() && h >= 0 && h < input[0].size());
}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-8/real-input.txt");

    long total = 0;

    auto nodes = parse_input(input);
    print(nodes);

    int antenodes[input.size()][input[0].size()];
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[0].size(); j++) {
            antenodes[i][j] = 0;
        }
    }

    for(auto it = nodes.cbegin(); it != nodes.cend(); ++it) {
        
        auto coords = it->second;

        for(int i = 0; i < coords.size(); i++) {
            for(int j = i + 1; j < coords.size(); j++) {

                Coord furthest_up;
                Coord furthest_down;

                if(coords[i].v < coords[j].v) {
                    furthest_up = coords[i];
                    furthest_down = coords[j];
                } else {
                    furthest_up = coords[j];
                    furthest_down = coords[i];
                }

                int v_diff = abs(furthest_up.v - furthest_down.v);
                int h_diff = abs(furthest_up.h - furthest_down.h);

                if(furthest_down.h <= furthest_up.h) {
                    if(is_valid(furthest_down.v + v_diff, furthest_down.h - h_diff, input)) {
                        antenodes[furthest_down.v + v_diff][furthest_down.h - h_diff] = 1;
                        input[furthest_down.v + v_diff][furthest_down.h - h_diff] = '#';
                    }
                    if(is_valid(furthest_up.v - v_diff, furthest_up.h + h_diff, input)) {
                        antenodes[furthest_up.v - v_diff][furthest_up.h + h_diff] = 1;
                        input[furthest_up.v - v_diff][furthest_up.h + h_diff] = '#';
                    }
                } else {
                    if(is_valid(furthest_down.v + v_diff, furthest_down.h + h_diff, input)) {
                        antenodes[furthest_down.v + v_diff][furthest_down.h + h_diff] = 1;
                        input[furthest_down.v + v_diff][furthest_down.h + h_diff] = '#';
                    }
                    if(is_valid(furthest_up.v - v_diff, furthest_up.h - h_diff, input)) {
                        antenodes[furthest_up.v - v_diff][furthest_up.h - h_diff] = 1;
                        input[furthest_up.v - v_diff][furthest_up.h - h_diff] = '#';
                    }
                }
            }
        }
    }

    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[0].size(); j++) {
            cout << input[i][j] << " ";
            if(antenodes[i][j] == 1) {
                total++;
            }
        }
        cout << endl;
    }

    cout << "Part one: " << total << endl;

}

void part_two() {

 const auto io = IO();
    auto input = io.readFile("./io/day-8/real-input.txt");

    long total = 0;

    auto nodes = parse_input(input);
    print(nodes);

    int antenodes[input.size()][input[0].size()];
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[0].size(); j++) {
            antenodes[i][j] = 0;
        }
    }

    for(auto it = nodes.cbegin(); it != nodes.cend(); ++it) {
        
        auto coords = it->second;

        for(int i = 0; i < coords.size(); i++) {
            for(int j = i + 1; j < coords.size(); j++) {

                Coord furthest_up;
                Coord furthest_down;

                antenodes[coords[i].v][coords[i].h] = 1;
                antenodes[coords[j].v][coords[j].h] = 1;

                if(coords[i].v < coords[j].v) {
                    furthest_up = coords[i];
                    furthest_down = coords[j];
                } else {
                    furthest_up = coords[j];
                    furthest_down = coords[i];
                }

                int v_diff = abs(furthest_up.v - furthest_down.v);
                int h_diff = abs(furthest_up.h - furthest_down.h);

                if(furthest_down.h <= furthest_up.h) {
                    int new_v = furthest_down.v + v_diff;
                    int new_h = furthest_down.h - h_diff;
                    while(is_valid(new_v, new_h, input)) {
                        antenodes[new_v][new_h] = 1;
                        input[new_v][new_h] = '#';
                        new_v += v_diff;
                        new_h -= h_diff;
                    }

                    new_v = furthest_up.v - v_diff;
                    new_h = furthest_up.h + h_diff;
                    while(is_valid(new_v, new_h, input)) {
                        antenodes[new_v][new_h] = 1;
                        input[new_v][new_h] = '#';
                        new_v -= v_diff;
                        new_h += h_diff;
                    }
                } else {

                    int new_v = furthest_down.v + v_diff;
                    int new_h = furthest_down.h + h_diff;
                    while(is_valid(new_v, new_h, input)) {
                        antenodes[new_v][new_h] = 1;
                        input[new_v][new_h] = '#';
                        new_v += v_diff;
                        new_h += h_diff;
                    }

                    new_v = furthest_up.v - v_diff;
                    new_h = furthest_up.h - h_diff;
                    while(is_valid(new_v, new_h, input)) {
                        antenodes[new_v][new_h] = 1;
                        input[new_v][new_h] = '#';
                        new_v -= v_diff;
                        new_h -= h_diff;
                    }
                }
            }
        }
    }

    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[0].size(); j++) {
            cout << input[i][j] << " ";
            if(antenodes[i][j] == 1) {
                total++;
            }
        }
        cout << endl;
    }

    cout << "Part one: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}