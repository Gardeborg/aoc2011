#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

void produce_fishes(std::map<int, long long>& fishes, int days) {
    if(days == 0)
        return;

    long long spawning_fishes = fishes[0];
    for(int i = 0; i < 8; i++) {
        fishes[i] = fishes[i+1];
    }
    fishes[6] += spawning_fishes;
    fishes[8] = spawning_fishes;

    produce_fishes(fishes, --days);
}

int main() {

    std::ifstream file("input");
    std::string line_str;
    std::map<int, long long> fish_map;
    int cycle = 8;

    while(cycle) {
        fish_map[cycle] = 0;
        cycle--;
    }

    while(std::getline(file, line_str)) {
        std::replace(line_str.begin(), line_str.end(),',',' ');
        std::stringstream ssline(line_str);
        int timer;
        while(ssline >> timer) {
            fish_map[timer]++;
        }
    }
    produce_fishes(fish_map, 256);
    long long sum = 0;
    for(auto [timer, fishes] : fish_map) {
        sum += fishes;
    }
    std::cout << sum;
    return 0;
}