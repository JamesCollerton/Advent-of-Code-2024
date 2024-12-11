#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>
#include <algorithm>
#include "../io/io.h"

using namespace std;

vector<long> parse_input(const string &input) {
    vector<long> result;
    for(int i = 0; i < input.size(); i++) {
        result.push_back(input[i] - '0');
    }
    return result;
}

void part_one() {

    const auto io = IO();
    auto input = io.readFile("./io/day-9/real-input.txt")[0];
    auto input_nums = parse_input(input);

    long total = 0;

    int file = 0, pos = 0;

    vector<long> disk;

    while(pos < input_nums.size()) {
        if(pos % 2 == 0) {
            for(int i = 0; i < input_nums[pos]; i++) {
                disk.push_back(file);
            }
            file++;
        } else {
            for(int i = 0; i < input_nums[pos]; i++) {
                disk.push_back(-1);
            }
        }
        pos++;
    }

    int to_move = disk.size() - 1;
    int free = 0;

    while(free < to_move) {
        while(disk[free] != -1){
            free++;
        } 
        while(disk[to_move] == -1) {
            to_move--;
        }
        if(free < to_move) {
            disk[free] = disk[to_move];
            disk[to_move] = -1;
        }
    }

    for(int i = 0; i < disk.size(); i++) {
        if(disk[i] != -1) {
            total += i * disk[i];
        }
    }

    cout << "Part one: " << total << endl;

}

void part_two() {

    const auto io = IO();
    auto input = io.readFile("./io/day-9/real-input.txt")[0];
    auto input_nums = parse_input(input);

    long total = 0;

    long file = 0, pos = 0;

    vector<long> disk;

    while(pos < input_nums.size()) {
        if(pos % 2 == 0) {
            for(int i = 0; i < input_nums[pos]; i++) {
                disk.push_back(file);
            }
            file++;
        } else {
            for(int i = 0; i < input_nums[pos]; i++) {
                disk.push_back(-1);
            }
        }
        pos++;
    }

    long to_move = disk.size() - 1;

    set<long> seen;

    // While we can move any block
    while(to_move > 0) {

        // Find start of first disk block from end
        while(disk[to_move] == -1 && to_move > 0 && seen.find(disk[to_move]) != seen.end()) {
            to_move--;
        }

        // Measure disk block
        long file_size = 0;
        long file_type = disk[to_move];
        seen.insert(file_type);
        while(disk[to_move - file_size] == file_type && (to_move - file_size) >= 0) {
            file_size++;
        }

        // Find free blocks until one is big enough
        long free = 0;
        while(free < to_move && free < disk.size()) {

            // Find start of next free block
            while(disk[free] != -1 && free < disk.size()) {
                free++;
            }

            if(free < to_move) {
                
                // Measure free block
                long free_size = 0;
                while(disk[free + free_size] == -1 && (free + free_size < disk.size())) {
                    free_size++;
                }

                // If there is enough space
                if(free_size >= file_size) {
                    long counter = 0;

                    // Move this into the free space
                    long file_type = disk[to_move];
                    for(int i = 0; i < file_size; i++) {
                        disk[free + i] = file_type;
                    }

                    for(int i = 0; i < file_size; i++) {
                        disk[to_move - i] = -1;
                    }

                    // End
                    free = to_move + 1;
                } else {
                    free = free + free_size;
                }
            }
        }
        to_move = to_move - (file_size);

    }

    for(int i = 0; i < disk.size(); i++) {
        if(disk[i] != -1) {
            total += i * disk[i];
        }
    }

    cout << "Part two: " << total << endl;

}

int main() {

    part_one();
    part_two();

    return 0;
}