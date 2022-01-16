#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
    /*
    Find out digits:
    2 seg = 1
    3 seg = 7
    4 seg = 4
    5 seg = 2,3,5
    6 seg = 0,6,9
    7 seg = 8

    0,6,9 (6 seg)
    6 seg + 1 = 8 (7 seg) => 6
    6 seg + 4 = 8 (7 seg) => 0
    else 9

    2,3,5 (5 seg)
    5 seg + 4 = 8 => 2
    5 seg - 1 (2 seg) = 3 seg => 3
    else 5
    */

// First loop once through the vector and find 1,4,7,8
// Then use the rules above to figure out the rest of the digits
std::map<int, std::set<char>> map_digits(std::vector<std::set<char>>& patterns) {
    std::map<int, std::set<char>> digits{};
    for(auto& pattern: patterns) {
        if(pattern.size() == 2)
            digits[1] = pattern;
        else if(pattern.size() == 3)
            digits[7] = pattern;
        else if(pattern.size() == 4)
            digits[4] = pattern;
        else if(pattern.size() == 7)
            digits[8] = pattern;
    }

    for(auto& pattern: patterns) {
        if(pattern.size() == 5) {
            std::set<char> tmp;
            std::merge(pattern.begin(), pattern.end(), 
                       digits[4].begin(), digits[4].end(), 
                       std::inserter(tmp, tmp.begin()));
            if(tmp.size() == 7) {
                digits[2] = pattern;
                continue;
            }
            tmp.clear();
            std::set_difference(pattern.begin(), pattern.end(), 
                                digits[1].begin(), digits[1].end(), 
                                std::inserter(tmp, tmp.begin()));
            if(tmp.size() == 3) {
                digits[3] = pattern;
                continue;
            }
            digits[5] = pattern;
        }
        if(pattern.size() == 6) {
            std::set<char> tmp;
            std::merge(pattern.begin(), pattern.end(), 
                       digits[1].begin(), digits[1].end(), 
                       std::inserter(tmp, tmp.begin()));
            if(tmp.size() == 7) {
                digits[6] = pattern;
                continue;
            }
            tmp.clear();
            std::merge(pattern.begin(), pattern.end(), 
                       digits[4].begin(), digits[4].end(), 
                       std::inserter(tmp, tmp.begin()));
            if(tmp.size() == 7) {
                digits[0] = pattern;
                continue;
            }
            digits[9] = pattern;
        }
    }
    return digits;
}

int part1(std::vector<std::string>& lines) {
    int sum = 0;
    std::string output;
    for(auto line : lines) {
        std::stringstream ss_output(line.substr(line.find('|') + 2));
        while(ss_output >> output) {
            switch(output.length()) {
                case 2: //one
                case 3: //seven
                case 4: //four
                case 7: //eight
                    sum++;
                    break;
            }
        }
    }
    return sum;
}

int part2(std::vector<std::string>& lines) {
    int sum = 0;
    std::set<char> digit;
    std::vector<std::set<char>> patterns;
    std::string signal;
    std::string output_value;

    for(auto line : lines) {
        std::stringstream signals(line.substr(0, line.find('|')));
        while(signals >> signal) {
            for(char segment : signal) {
                digit.insert(segment);
            }
            patterns.push_back(digit);
            digit.clear();
        }
        std::map<int, std::set<char>> digits = map_digits(patterns);
        std::stringstream output(line.substr(line.find('|') + 2));
        output_value = "";
        while(output >> signal) {
            for(char segment : signal) {
                digit.insert(segment);
            }
            for(auto [key, value] : digits) {
                if(value == digit) {
                    output_value.append(std::to_string(key));
                    break;
                }
            }
            digit.clear();
        }
        sum += std::stoi(output_value);
    }
    return sum;
}

int main() {
    std::ifstream file("input");
    std::string line;
    std::vector<std::string> lines;
    while(std::getline(file, line)) {
        lines.push_back(line);
    }
    cout << "Part 1: " << part1(lines) << endl;
    cout << "Part 2: " << part2(lines) << endl;
}