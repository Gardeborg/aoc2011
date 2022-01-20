#include <fstream>
#include <iostream>
#include <vector>

// It is enough to compare head and tail in the sliding window
template <class T>
int get_num_increased(std::vector<T>& values, int mean_size = 1) {
    int tail_index = 0;
    int head_index = mean_size;
    int result = 0;
    while(head_index < values.size()) {
        if(values.at(tail_index) < values.at(head_index)) {
            result++;
        }
        head_index++;
        tail_index++;
    }
    return result;
}

int main() {
    std::ifstream input_file("input");
    std::vector<int> depths;
    std::string depth;
    while(getline(input_file, depth)) {
        depths.push_back(std::stoi(depth));
    }
    std::cout << "Number of increasing measurements: " << get_num_increased(depths) << std::endl;
    std::cout << "Number of increasing measurements using "
                  "sliding window of three measurements: " << get_num_increased(depths, 3) << std::endl;
}