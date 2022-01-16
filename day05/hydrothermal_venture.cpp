#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>

struct point {
    int x;
    int y;
};

void populate_map(std::map<std::pair<int,int>, int>& points, int x1, int y1, int x2, int y2) {

    // vertical
    if(y1 == y2) {
        int x_min = std::min(x1,x2);
        int x_max = std::max(x1,x2);
        for(int x = x_min; x <= x_max; x++) {
            if(points.find(std::make_pair(x,y1)) != points.end()) {
                ++points[std::make_pair(x,y1)];
            }
            else
                points[std::make_pair(x,y1)] = 1;
        }
    }
    // horizontal
    else if(x1 == x2) {
        int y_min = std::min(y1,y2);
        int y_max = std::max(y1,y2);
        for(int y = y_min; y <= y_max; y++) {
            if(points.find(std::make_pair(x1,y)) != points.end()) {
                ++points[std::make_pair(x1,y)];
            }
            else
                points[std::make_pair(x1,y)] = 1;
        }
    }
    // Diagonal line
    else if(abs(x1 - x2) == abs(y1 - y2)) {
        bool x_increasing = false;
        bool y_increasing = false;
        if(x2 > x1)
            x_increasing = true;
        if(y2 > y1)
            y_increasing = true;

        int x_temp = x1;
        int y_temp = y1;

        while(true) {
            if(points.find(std::make_pair(x_temp,y_temp)) != points.end()) {
                ++points[std::make_pair(x_temp,y_temp)];
            }
            else
                points[std::make_pair(x_temp,y_temp)] = 1;

            if(x_temp == x2)
                break;

            x_increasing ? x_temp++ : x_temp--;
            y_increasing ? y_temp++ : y_temp--;
        }
    }
}

int main() {

    std::ifstream file("input");
    std::string line_str;
    int x1, x2, y1, y2;

    std::map<std::pair<int,int>, int> points;
    while(std::getline(file, line_str)) {
        // std::cout << line_str << std::endl;
        std::replace_if(line_str.begin(), line_str.end(),
            [](auto& c) {
                if(c == ',') return true;
                if(c == '-') return true;
                if(c == '>') return true;
                return false;
            }, ' ');
        std::stringstream ss(line_str);
        ss >> x1 >> y1 >> x2 >> y2;

        populate_map(points, x1, y1, x2, y2);
        // std::cout << x1 << x2 << y1 << y2 << std::endl;
    }

    // for(auto [key, value] : points)
    //      std::cout << key.first << key.second << " : " << value << std::endl;

    int score = 0;
    for(auto [key, value] : points) {
        if(value >= 2)
            score++;
    }
    std::cout << points.size() << std::endl;
    std::cout << score << std::endl;

    return 0;
}