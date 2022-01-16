#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>

char get_opposite(char bracket) {
    char opposite;
    switch(bracket) {
        case '{': opposite = '}'; break;
        case '}': opposite = '{'; break;
        case '(': opposite = ')'; break;
        case ')': opposite = '('; break;
        case '[': opposite = ']'; break;
        case ']': opposite = '['; break;
        case '<': opposite = '>'; break;
        case '>': opposite = '<'; break;
    }
    return opposite;
}

int get_points_1(char bracket) {
    int points;
    switch(bracket) {
        case '}': points = 1197; break;
        case ')': points = 3; break;
        case ']': points = 57; break;
        case '>': points = 25137; break;
    }
    return points;
}

int get_points_2(char bracket) {
    int points;
    switch(bracket) {
        case '}': points = 3; break;
        case ')': points = 1; break;
        case ']': points = 2; break;
        case '>': points = 4; break;
    }
    return points;
}

int part1(const std::vector<std::string>& lines) {
    int points;
    for(auto& line : lines) {
        std::deque<char> brackets;
        for(auto bracket : line) {
            if(bracket == '{' || bracket == '(' || bracket == '[' || bracket == '<') {
                brackets.push_front(bracket);
            }
            if(bracket == '}' || bracket == ')' || bracket == ']' || bracket == '>') {
                if(get_opposite(bracket) != brackets.front()) {
                    points += get_points_1(bracket);
                    break;
                }
                else
                    brackets.pop_front();
            }
        }
    }
    return points;
}

long long part2(const std::vector<std::string>& lines) {
    std::vector<long long> points;
    for(auto& line : lines) {
        bool illegal = false;
        std::deque<char> brackets;
        for(auto bracket : line) {
            if(bracket == '{' || bracket == '(' || bracket == '[' || bracket == '<') {
                brackets.push_front(bracket);
            }
            if(bracket == '}' || bracket == ')' || bracket == ']' || bracket == '>') {
                if(get_opposite(bracket) != brackets.front()) {
                    illegal = true;
                    break;
                }
                else
                    brackets.pop_front();
            }
        }
        if(!illegal) {
            // Count the values of the missing brackets
            long long sum = 0;
            for(auto bracket : brackets) {
                int value = get_points_2(get_opposite(bracket));
                sum *= 5;
                sum +=value;
            }
            points.push_back(sum);
        }
    }
    std::sort(points.begin(), points.end());
    return points[points.size() / 2];
}

int main() {
    std::ifstream file("input");
    std::string line;
    std::vector<std::string> lines;

    while(std::getline(file, line)) {
        lines.push_back(line);
    }

    std::cout << part1(lines) << std::endl;
    std::cout << part2(lines) << std::endl;

    return 0;
}