#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include <algorithm>
//#include <stdlib.h>

using std::string;
using std::vector;

int count_ones(std::vector<string> binary_values, int digit_pos) {
    int result = std::count_if(binary_values.begin(), binary_values.end(),
                    [digit_pos](string& s){ return s[digit_pos] == '1'; });
    return result;
}

std::vector<int> count_ones(std::vector<string> binary_values) {
    std::vector<int> ones_count(binary_values.at(0).size());
    int digit_pos = 0;
    while(digit_pos < ones_count.size()) {
        ones_count[digit_pos] = count_ones(binary_values, digit_pos);
        digit_pos++;
    }
    return ones_count;
}

int part1(vector<string>& binary_codes) {
    std::vector<int> ones_count = count_ones(binary_codes);

    uint gamma = 0;
    uint epsilon = 0;
    int digit_pos = ones_count.size();
    for(auto ones : ones_count) {
        digit_pos--;
        if(ones > (binary_codes.size() / 2)) {
            gamma |= 1 << digit_pos;
            epsilon |= 0 << digit_pos;
        }
        else {
            gamma |= 0 << digit_pos;
            epsilon |= 1 << digit_pos;
        }
    }
    return gamma * epsilon;
}

string discard_values(vector<string> binary_codes, int position, bool keep_most) {
    if(binary_codes.size() == 1) {
        return binary_codes.at(0);
    }
    int num_ones = count_ones(binary_codes, position);
    int digit_to_keep = 0;
    if(keep_most)
        digit_to_keep = num_ones >= (binary_codes.size() / 2.0) ? 1 : 0;
    else
        digit_to_keep = num_ones >= (binary_codes.size() / 2.0) ? 0 : 1;
    auto it = std::remove_if(binary_codes.begin(), binary_codes.end(),
                    [=](string& s) { return std::stoi(s.substr(position, 1)) != digit_to_keep;});
    binary_codes.erase(it, binary_codes.end());
    return discard_values(binary_codes, ++position, keep_most);
}

std::tuple<int, int> part2(vector<string>& binary_codes) {
    int position = 0;
    int oxygen_rating = std::stoi(discard_values(binary_codes, position, true), nullptr, 2);
    int scrubber_rating = std::stoi(discard_values(binary_codes, position, false), nullptr, 2);
    return {oxygen_rating, scrubber_rating};
}

int main() {
    std::ifstream input_file("input");
    vector<string> diagnostic_report{};
    string command;
    while(std::getline(input_file, command)) {
        diagnostic_report.push_back(command);
    }
    std::cout << part1(diagnostic_report) << std::endl;

    int oxygen_rating;
    int scrubber_rating;
    std::tie(oxygen_rating, scrubber_rating) = part2(diagnostic_report);
    std::cout << "Oxygen rating: " << oxygen_rating << std::endl;
    std::cout << "Scrubber rating: " << scrubber_rating << std::endl;
    std::cout << oxygen_rating * scrubber_rating << std::endl;
}