#include <iostream>
#include <sstream>
#include <regex>
#include <map>
#include "../io/io.h"

using namespace std;

auto one_total = 0;
int one_num_lines;
int one_num_letters;

void recursiveFindXmas(int line_increment, int letter_increment, int line, int letter, int xmas_pos, std::vector<std::string> input) {
    
    if(xmas_pos == 4) {
        one_total++;
    } else if(line < 0 || line > one_num_lines || letter < 0 || letter > one_num_letters) {
        return;
    } else if(input[line][letter] != "XMAS"[xmas_pos]) {
        return;
    }

    recursiveFindXmas(line_increment, letter_increment, line + line_increment, letter + letter_increment, xmas_pos + 1, input);

}

void partOne() {

    const auto io = IO();
    const auto input = io.readFile("./io/day-4/real-input.txt");

    one_num_lines = input.size();
    one_num_letters = input[0].size();

    for(int i = 0; i < one_num_lines; i++) {
        for(int j = 0; j < one_num_letters; j++) {
            for(int line_increment = -1; line_increment <= 1; line_increment++) {
                for(int letter_increment = -1; letter_increment <= 1; letter_increment++) {
                    if(!(line_increment == 0 && letter_increment == 0)) {
                        recursiveFindXmas(line_increment, letter_increment, i, j, 0, input);
                    }
                }
            }
        }
    }

    cout << "Part one: " << one_total << endl;

}

auto two_total = 0;
int two_num_lines;
int two_num_letters;

void partTwo() {

    const auto io = IO();
    const auto input = io.readFile("./io/day-4/real-input.txt");

    two_num_lines = input.size();
    two_num_letters = input[0].size();

    for(int i = 1; i < two_num_lines - 1; i++) {
        for(int j = 1; j < two_num_letters - 1; j++) {
            if(input[i][j] == 'A') {
                if((input[i - 1][j - 1] == 'M' && input[i + 1][j + 1] == 'S') || (input[i - 1][j - 1] == 'S' && input[i + 1][j + 1] == 'M')) {
                    if((input[i - 1][j + 1] == 'M' && input[i + 1][j - 1] == 'S') || (input[i - 1][j + 1] == 'S' && input[i + 1][j - 1] == 'M')) {
                        two_total++;
                    }
                }
            }
        }
    }

    cout << "Part two: " << two_total << endl;

}

int main() {

    partOne();
    partTwo();

    return 0;
}