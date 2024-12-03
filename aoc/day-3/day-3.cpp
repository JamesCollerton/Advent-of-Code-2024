#include <iostream>
#include <sstream>
#include <regex>
#include <map>
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
                if(substr.find(',') != string::npos) {
                    auto left = substr.substr(0, substr.find(','));
                    auto right = substr.substr(substr.find(',') + 1);

                    if(is_number(left) && is_number(right)) {
                        total += stoi(left) * stoi(right);
                    }
                }
            }
            
        }
        mul_location = input.find("mul", mul_location + 1);
    }

    cout << "Part one: " << total << endl;

}

void partTwo() {

    const auto io = IO();
    const auto input = io.readFile("./io/day-3/real-input.txt")[0];

    int total = 0;

    auto mul_location = input.find("mul");
    auto prev_mul_location = 0;

    auto enabled = true;

    while(mul_location != string::npos) {

        auto ss = string(&input[prev_mul_location], &input[mul_location]);
        auto do_l = ss.rfind("do()");
        auto dont_l = ss.rfind("don't()");

        if(do_l == string::npos && dont_l == string::npos) {
            enabled = enabled;
        } else if(do_l == string::npos) {
            enabled = false;
        } else if(dont_l == string::npos) {
            enabled = true;
        } else {
            enabled = do_l >= dont_l;
        }

        if(enabled && input[mul_location + 3] == '(') {
            
            const auto cb_location = input.find(")", mul_location);

            if(cb_location != string::npos) {

                auto substr = std::string(&input[mul_location + 4], &input[cb_location]);
                if(substr.find(',') != string::npos) {
                    auto left = substr.substr(0, substr.find(','));
                    auto right = substr.substr(substr.find(',') + 1);

                    if(is_number(left) && is_number(right)) {
                        total += stoi(left) * stoi(right);
                    }
                }
            }
            
        }
        prev_mul_location = mul_location;
        mul_location = input.find("mul", mul_location + 1);
    }

    cout << "Part two: " << total << endl;

}

int main() {

    partOne();
    partTwo();

    return 0;
}