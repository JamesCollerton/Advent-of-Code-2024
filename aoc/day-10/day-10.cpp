#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../io/io.h"

using namespace std;

int recursive_find_trails(vector<vector<int>> &trails, int v, int h, int pos) {
    if(v >= trails.size() || v < 0 || h >= trails[0].size() || h < 0 || trails[v][h] != pos) {
        return 0;
    } else if(pos == 9) {
        trails[v][h] = -1;
        return 1;  
    }
    return  recursive_find_trails(trails, v, h + 1, pos + 1) +
            recursive_find_trails(trails, v, h - 1, pos + 1) +
            recursive_find_trails(trails, v + 1, h, pos + 1) +
            recursive_find_trails(trails, v - 1, h, pos + 1);
}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-10/real-input.txt");

    vector<vector<int>> trails;

    for(int i = 0; i < input.size(); i++) {
        vector<int> row;
        for(int j = 0; j < input[0].size(); j++) {
            row.push_back(input[i][j] - '0');
        }
        trails.push_back(row);
    }

    long total = 0;

    for(int i = 0; i < trails.size(); i++) {
        for(int j = 0; j < trails[i].size(); j++) {
            auto new_trails = trails;
            total += recursive_find_trails(new_trails, i, j, 0);
        }
    }

    cout << "Part one: " << total << endl;

}

int recursive_find_all_trails(vector<vector<int>> &trails, int v, int h, int pos) {
    if(v >= trails.size() || v < 0 || h >= trails[0].size() || h < 0 || trails[v][h] != pos) {
        return 0;
    } else if(pos == 9) {
        return 1;  
    }
    return  recursive_find_all_trails(trails, v, h + 1, pos + 1) +
            recursive_find_all_trails(trails, v, h - 1, pos + 1) +
            recursive_find_all_trails(trails, v + 1, h, pos + 1) +
            recursive_find_all_trails(trails, v - 1, h, pos + 1);
}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-10/real-input.txt");

    vector<vector<int>> trails;

    for(int i = 0; i < input.size(); i++) {
        vector<int> row;
        for(int j = 0; j < input[0].size(); j++) {
            row.push_back(input[i][j] - '0');
        }
        trails.push_back(row);
    }

    long total = 0;

    for(int i = 0; i < trails.size(); i++) {
        for(int j = 0; j < trails[i].size(); j++) {
            auto new_trails = trails;
            total += recursive_find_all_trails(new_trails, i, j, 0);
        }
    }

    cout << "Part one: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}