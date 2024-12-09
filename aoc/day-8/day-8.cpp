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
            cout << "[" << coord.h << "," << coord.v << "] ";
        }
        cout << endl;
    }

}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-8/test-input.txt");

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

        for(int v = 0; v < input.size(); v++) {
            for(int h = 0; h < input[0].size(); h++) {
                for(int i = 0; i < coords.size(); i++) {
                    for(int j = i + 1; j < coords.size(); j++) {

                        int dist_1 = abs(v - coords[i].v) + abs(h - coords[i].h);
                        int dist_2 = abs(v - coords[j].v) + abs(h - coords[j].h);

                        int v1 = abs(v - coords[i].v);
                        int v2 = abs(v - coords[j].v);
                        int v_diff = abs(coords[i].v - coords[j].v);

                        if(dist_1 == 2 * dist_2 || dist_2 == 2 * dist_1) {
                            // cout << "v: " << v << ", h:" << h << endl;
                            // cout << "v.1: " << coords[i].v << ", h.1: " << coords[i].h << endl;
                            // cout << "v.2: " << coords[j].v << ", h.2: " << coords[j].h << endl;
                            antenodes[v][h] = 1;
                        }

                    }
                }
            }
        }
    }

    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[0].size(); j++) {
            if(antenodes[i][j] == 1) {
                total++;
            }
        }
    }

    cout << "Part one: " << total << endl;

}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-7/real-input.txt");

    long total = 0;

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}