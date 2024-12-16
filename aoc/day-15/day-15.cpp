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

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-15/real-input.txt");

    vector<string> grid;

    int counter = 0;
    while(input[counter] != "") {
        grid.push_back(input[counter++]);
    }
    counter++;
    string instructions;
    while(counter < input.size()) {
        instructions += input[counter++];
    }

    int v, h;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            if(input[i][j] == '@') {
                v = i;
                h = j;
            }
        }
    }

    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // cout << "v: " << v << "h: " << h << endl;

    for(int i = 0; i < instructions.size(); i++) {

        cout << instructions[i] << endl;

        if(instructions[i] == '^') {

            // cout << "Going up";

            // Find the first box that's either a wall or a space
            int curr_v = v - 1;
            while(curr_v >= 0 && grid[curr_v][h] == 'O') {
                curr_v--;
            }
            
            // cout << "curr_v: " << curr_v << endl;

            // If the box is a space
            if(curr_v >= 0 && grid[curr_v][h] == '.') {
                
                //Go back down and copy everything up
                while(curr_v < v) {
                    grid[curr_v][h] = grid[curr_v + 1][h];
                    curr_v++;
                }

                // Our previous position is a space and we move up one
                grid[v][h] = '.';
                v = v - 1;
            }
        }
        if(instructions[i] == '>') {

            // cout << "Going right";

            int curr_h = h + 1;
            while(curr_h < grid[v].size() && grid[v][curr_h] == 'O') {
                curr_h++;
            }

            // cout << "curr_h: " << curr_h << endl;

            if(curr_h < grid[v].size() && grid[v][curr_h] == '.') {
                while(curr_h > h) {
                    grid[v][curr_h] = grid[v][curr_h - 1];
                    curr_h--;
                }
                grid[v][h] = '.';
                h = h + 1;
            }
        }
        if(instructions[i] == 'v') {

            // cout << "Going down";

            int curr_v = v + 1;
            while(curr_v < grid.size() && grid[curr_v][h] == 'O') {
                curr_v++;
            }
            if(curr_v < grid.size() && grid[curr_v][h] == '.') {
                while(curr_v > v) {
                    grid[curr_v][h] = grid[curr_v - 1][h];
                    curr_v--;
                }
                grid[v][h] = '.';
                v = v + 1;
            }
        }
        if(instructions[i] == '<') {
            
            // cout << "Going left";
            
            int curr_h = h - 1;
            while(curr_h >= 0 && grid[v][curr_h] == 'O') {
                curr_h--;
            }

            // cout << "curr_h: " << curr_h << endl;

            if(curr_h >= 0 && grid[v][curr_h] == '.') {
                while(curr_h < h) {
                    grid[v][curr_h] = grid[v][curr_h + 1];
                    curr_h++;
                }
                grid[v][h] = '.';
                h = h - 1;
            }
        }

        // for(int i = 0; i < grid.size(); i++) {
        //     for(int j = 0; j < grid[i].size(); j++) {
        //         cout << grid[i][j];
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }

    long total = 0;

    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            if(grid[i][j] == 'O') {
                total += (100 * i) + j;
            }
        }
        cout << endl;
    }


    cout << "Part one: " << total << endl;

}

// Just program to display the output and look for a Christmas tree.
void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-15/test-input-smaller.txt");

    long total = 0;

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}