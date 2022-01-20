#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <numeric>

using std::string;

void part1() {
    std::ifstream input_file("input");
    int depth = 0;
    int horizontal = 0;

    std::string command;
    while(std::getline(input_file, command)) {
        std::string direction{command.substr(0, command.find(" "))};
        int distance{std::stoi(command.substr(command.find(" ") + 1))};

        if(direction == "up")
            depth -= distance;
        else if(direction == "down")
            depth += distance;
        else if(direction == "forward")
            horizontal += distance;
    }
    std::cout << "Horizontal distance: " << horizontal << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << horizontal * depth << std::endl;
}

void part1(std::unordered_map<std::string, std::vector<int>>& directions) {
    int depth = 0;
    int horizontal = 0;
    for(auto& [direction, distance] : directions) {
        auto res = std::accumulate(distance.begin(), distance.end(), 0);
        if(direction == "up")
            depth -= res;
        else if(direction == "down")
            depth += res;
        else if(direction == "forward")
            horizontal += res;
    }
    std::cout << "Horizontal distance: " << horizontal << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << horizontal * depth << std::endl;
}

// Does not work, order is important and the map does not contain that information
// void part2(std::unordered_map<std::string, std::vector<int>>& directions) {
//     int aim = 0;
//     int depth = 0;
//     int horizontal = 0;
//     for(auto& direction : directions) {
//         for(auto& distance : directions.second) {
//             if(direction == "up")
//                 aim -= distance;
//             else if(direction == "down")
//                 aim += distance;
//             else if(direction == "forward") {
//                 horizontal += distance;
//                 depth += distance * aim;
//             }
//         }
//     }
//     std::cout << "Horizontal distance: " << horizontal << std::endl;
//     std::cout << "Depth: " << depth << std::endl;
//     std::cout << horizontal * depth << std::endl;
// }

void part2() {
    std::ifstream input_file("input");
    int aim = 0;
    int depth = 0;
    int horizontal = 0;
    std::string command;
    while(std::getline(input_file, command)) {
        std::string direction{command.substr(0, command.find(" "))};
        int distance{std::stoi(command.substr(command.find(" ") + 1))};

        if(direction == "up")
            aim -= distance;
        else if(direction == "down")
            aim += distance;
        else if(direction == "forward") {
            horizontal += distance;
            depth += distance * aim;
        }
    }
    std::cout << "Horizontal distance: " << horizontal << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << horizontal * depth << std::endl;
}

int main() {
    std::ifstream input_file("input");
    string command;
    std::unordered_map<string, std::vector<int>> directions{};
    while(std::getline(input_file, command)) {
        string direction{command.substr(0, command.find(" "))};
        int distance{std::stoi(command.substr(command.find(" ") + 1))};
        if(directions.find(direction) != directions.end()) {
            directions[direction].emplace_back(distance);
        }
        else {
            std::pair<string, std::vector<int>> entry{direction, {distance}};
            directions.insert(entry);
        }
    }
            
    // Read input to a vector of pairs?
    part1();
    part1(directions);
    part2();
}
