#include <array>
#include <iostream>
#include <fstream>
#include <vector>


struct octopus {
    int energy_level;
    bool flashed = false;
};

bool valid(std::vector<std::vector<octopus>> octopuses, int row, int col) {
    return (row >= 0) && (row < octopuses.size()) && (col >= 0) && (col < octopuses[0].size());
}

void spread_energy(std::vector<std::vector<octopus>>& octopuses, int row, int col, int& acc) {
    acc += 1;
    std::vector<int> x_offset{-1, 0, 1, -1, 1, -1, 0, 1};
    std::vector<int> y_offset{-1, -1, -1, 0, 0, 1, 1, 1};
    // Increase neighbours because of flash
    for(int offset_index = 0; offset_index < x_offset.size(); ++offset_index) {
        int deltaY = y_offset[offset_index];
        int deltaX = x_offset[offset_index];
        if(valid(octopuses, row + deltaY, col + deltaX))
            octopuses[row + deltaY][col + deltaX].energy_level += 1;
    }
    // Check neigbours if they are over 9
    for(int offset_index = 0; offset_index < x_offset.size(); ++offset_index) {
        int deltaY = y_offset[offset_index];
        int deltaX = x_offset[offset_index];
        if(valid(octopuses, row + deltaY, col + deltaX) && 
           octopuses[row + deltaY][col + deltaX].energy_level > 9 && 
           !octopuses[row + deltaY][col + deltaX].flashed) {
            octopuses[row+ deltaY][col + deltaX].flashed = true; // Mark that it flashed
            spread_energy(octopuses, row + deltaY, col + deltaX, acc);
        }
    }
}

int part1(std::vector<std::vector<octopus>> octopuses) {

    std::vector<int> x_offset{-1, 0, 1, -1, 1, -1, 0, 1};
    std::vector<int> y_offset{-1, -1, -1, 0, 0, 1, 1, 1};
    int iteration = 0;
    int acc = 0;

    auto print = [&](){
        std::cout << std::string(octopuses.size(), '=') << '\n';
        for(int row = 0; row < octopuses.size(); ++row) {
            for(int col = 0; col < octopuses[row].size(); ++col ) {
                std::cout << octopuses[row][col].energy_level;
            }
            std::cout << '\n';
        }
    };

    while(iteration++ < 100) {
        // Increase all by 1
        for(int row = 0; row < octopuses.size(); ++row) {
            for(int col = 0; col < octopuses[row].size(); ++col ) {
                octopuses[row][col].energy_level += 1;
            }
        }

        // Flash if over 9
        for(int row = 0; row < octopuses.size(); ++row) {
            for(int col = 0; col < octopuses[row].size(); ++col ) {
                if(octopuses[row][col].energy_level > 9 && !octopuses[row][col].flashed) {
                    octopuses[row][col].flashed = true; // Mark that it flashed
                    spread_energy(octopuses, row, col, acc);
                }
            }
        }

        // Set flashed to 0
        for(int row = 0; row < octopuses.size(); ++row) {
            for(int col = 0; col < octopuses[row].size(); ++col ) {
                if(octopuses[row][col].flashed) {
                    octopuses[row][col].energy_level = 0;
                    octopuses[row][col].flashed = false;
                }
            }
        }
    }

    return acc;
}

int part2(std::vector<std::vector<octopus>> octopuses) {
    std::vector<int> x_offset{-1, 0, 1, -1, 1, -1, 0, 1};
    std::vector<int> y_offset{-1, -1, -1, 0, 0, 1, 1, 1};
    int iteration = 0;
    int acc = 0;

    auto print = [&](){
        std::cout << std::string(octopuses.size(), '=') << '\n';
        for(int row = 0; row < octopuses.size(); ++row) {
            for(int col = 0; col < octopuses[row].size(); ++col ) {
                std::cout << octopuses[row][col].energy_level;
            }
            std::cout << '\n';
        }
    };

    while(true) {
        ++iteration;
        // Increase all by 1
        for(int row = 0; row < octopuses.size(); ++row) {
            for(int col = 0; col < octopuses[row].size(); ++col ) {
                octopuses[row][col].energy_level += 1;
            }
        }

        // Flash if over 9
        for(int row = 0; row < octopuses.size(); ++row) {
            for(int col = 0; col < octopuses[row].size(); ++col ) {
                if(octopuses[row][col].energy_level > 9 && !octopuses[row][col].flashed) {
                    octopuses[row][col].flashed = true; // Mark that it flashed
                    spread_energy(octopuses, row, col, acc);
                }
            }
        }

        // Set flashed to 0 and check synchronization
        bool synchronized = true;
        for(int row = 0; row < octopuses.size(); ++row) {
            for(int col = 0; col < octopuses[row].size(); ++col ) {
                if(octopuses[row][col].flashed) {
                    octopuses[row][col].energy_level = 0;
                    octopuses[row][col].flashed = false;
                }
                else
                    synchronized = false;
            }
        }
        if(synchronized)
            break;
    }

    return iteration;
}

int main() {
    std::ifstream file("input");
    std::string line;
    std::vector<std::string> lines;
    std::vector<std::vector<octopus>> octopuses;
    int row = 0;
    while(std::getline(file, line)) {
        int col = 0;
        octopuses.push_back(std::vector<octopus>{});
        for(auto level : line) {
            octopuses[row].push_back(octopus{level - '0', false});
            ++col;
        }
        ++row;
        lines.push_back(line);
    }

    std::cout << "Part 1: " << part1(octopuses) << std::endl;
    std::cout << "Part 2: " << part2(octopuses) << std::endl;

    return 0;
}