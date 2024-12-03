#include <iostream>
#include <sstream>
#include "../io/io.h"

using namespace std;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void partOne() {

    const auto io = IO();
    const auto input = io.readFile("./io/day-3/real-input.txt")[0];

    int total = 0;

    auto mul_location = input.find("mul");
    while(mul_location != string::npos) {
        if(input[mul_location + 3] == '(') {
            
            const auto cb_location = input.find(")", mul_location);

            if(cb_location != string::npos) {

                auto substr = std::string(&input[mul_location + 4], &input[cb_location]);
                auto left = substr.substr(0, substr.find(','));
                auto right = substr.substr(substr.find(',') + 1);

                // cout << "Substr: " << substr << endl;

                if(is_number(left) && is_number(right)) {
                    total += stoi(left) * stoi(right);
                    cout << "Left: " << left << endl;
                    cout << "Right: " << right << endl;
                    cout << "Total: " << total << endl;
                }
            }
            
        }
        mul_location = input.find("mul", mul_location + 1);
    }

    cout << "Part one: " << total << endl;

}

void partTwo() {

    const auto io = IO();
    const auto input = io.readFile("./io/day-3/test-input.txt")[0];

    // auto total = 0;

    cout << "Part two: " << input << endl;

}

int main() {

    partOne();
    partTwo();

    return 0;
}