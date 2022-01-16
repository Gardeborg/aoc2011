#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

int get_above_index(int index, int line_length) {
    if(index - line_length > 0)
        return index - line_length;
    return -1;
}

int get_right_index(int index, int line_length) {
    if(index % line_length < (line_length - 1) )
        return index + 1;
    return -1;
}

int get_left_index(int index, int line_length) {
    if(index % line_length > 0)
        return index - 1;
    return -1;
}

int get_below_index(int index, int line_length, int total_size) {
    if(index + line_length < total_size)
        return index + line_length;
    return -1;
}

int check_neighbours(std::vector<int>& heights, int index, int line_length) {
    if(index == -1 || heights[index] == 9 || heights[index] == -1)
        return 0;
    else
        heights[index] = -1;
    return 1 +
           check_neighbours(heights, get_above_index(index, line_length), line_length) +
           check_neighbours(heights, get_right_index(index, line_length), line_length) +
           check_neighbours(heights, get_left_index(index, line_length), line_length) +
           check_neighbours(heights, get_below_index(index, line_length, heights.size()), line_length);
}

int part2(std::vector<int>& heights, int line_length, bool print_iterations = false) {
    std::vector<int> basin_sizes;
    int index = 0;

    auto print = [line_length](const std::vector<int> heights) {
        int index = 0;
        for(auto height : heights) {
            if(height == -1)
                height = 0; // Using 0 instead of -1 to not get alignment issues when printing
            std::cout<<height;
            ++index;
            if(index % line_length == 0) {
                 std::cout << '\n';
            }
        }
        std::cout << std::string(line_length, '=') << std::endl;
    };

    // Iterates over all heights. If a height is not 9 count the neighbours recursively. Mark all counted
    // heights in a basin as -1 to only check them once.
    for(auto& height : heights) {
        if(height != 9 && height != -1) {
            int basin_size = check_neighbours(heights, index, line_length);
            if(basin_size != 0)
                basin_sizes.push_back(basin_size);
            height = -1;
            if(print_iterations)
                print(heights);
        }
        ++index;
    }
    std::sort(basin_sizes.begin(), basin_sizes.end(), [](const auto& a, const auto& b) { return a > b;});
    int sum = basin_sizes[0] * basin_sizes[1] * basin_sizes[2];
    return sum;
}

std::vector<int> get_low_points(std::vector<int> heights, int line_length) {
    int index = 0;
    std::vector<int> low_points;
    for(auto height : heights) {
        // Set top, left, right and bottom values
        int top = 10, left = 10, right = 10, bottom = 10;
        if(index - (line_length - 1) > 0)
            top = heights[index - line_length];
        if(index % line_length > 0)
            left = heights[index - 1];
        if(index % line_length < (line_length - 1) )
            right = heights[index + 1];
        if(index + line_length < heights.size())
            bottom = heights[index + line_length];
        if(top > height && left > height && right > height && bottom > height)
            low_points.push_back(height);
        ++index;
    }
    return low_points;
}

int part1(std::vector<int>& heights, const int line_length) {
    std::vector<int> low_points = get_low_points(heights, line_length);
    int sum = 0;
    for(auto height : low_points) {
        sum = sum + height + 1;
    }
    return sum;
}

int main() {
    std::ifstream file("input");
    std::string line;
    std::vector<int> heights;

    std::getline(file, line);
    file.seekg(0);
    int line_length = line.size();

    /* I am using a single vector to store heights. Better then a matrix? Probably not,
       it requires some tricky index checks when looking up the neighbours */
    while(std::getline(file, line)) {
        for(const char val : line) {
            char tmp[2]{val, '\0'}; // Needed to create a null terminated string for strtol to work
            heights.push_back(std::strtol(tmp, nullptr, 0));
        }
    }
    std::cout << "Part 1: " << part1(heights, line_length) << std::endl;
    std::cout << "Part 2: " << part2(heights, line_length) << std::endl;
}