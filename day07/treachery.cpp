#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>

using std::chrono::high_resolution_clock;

auto timeFuncInvocation = 
    [](auto&& func, auto&&... params) {
        // get time before function invocation
        const auto& start = high_resolution_clock::now();
        // function invocation using perfect forwarding
        for(auto i = 0; i < 100/*largeNumber*/; ++i) {
            std::forward<decltype(func)>(func)(std::forward<decltype(params)>(params)...);
        }
        // get time after function invocation
        const auto& stop = high_resolution_clock::now();
        return (stop - start)/100/*largeNumber*/;
     };

// Sum of all integers from 0 to value
template<class T>
T sum(T value) {
    T sum = (value*(value + 1)) / 2;
    return sum;
}

// template<class T>
// T sum(T value) {
//     int sum = 0;
//     for(int i = 0; i <= value; ++i)
//         sum += i;
//     return sum;
// }

int find_min_fuel(std::vector<int> positions) {
    int min_pos = *std::min_element(positions.begin(), positions.end());
    int max_pos = *std::max_element(positions.begin(), positions.end());
    int sum_min_fuel = INT_MAX;
    int current_fuel;

    for(int i = min_pos; i < max_pos; i++) {
        current_fuel = 0;
        for(auto position : positions) {
            current_fuel += sum(abs(position - i));
        }
        if(current_fuel < sum_min_fuel)
            sum_min_fuel = current_fuel;
    }
    return sum_min_fuel;
}

int main() {
    std::ifstream file("input");
    std::string line_str;
    std::vector<int> positions;

    while(std::getline(file, line_str)) {
        std::replace(line_str.begin(), line_str.end(),',',' ');
        std::stringstream ssline(line_str);
        int position = 0;
        while(ssline >> position) {
            positions.push_back(position);
        }
    }
    // std::cout << timeFuncInvocation(find_min_fuel, positions).count() << std::endl;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    // Measuring time to compare formula vs loop
    auto t1 = high_resolution_clock::now();
    find_min_fuel(positions);
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);
    std::cout << ms_int.count() << "ms\n";

    std::cout << find_min_fuel(positions) << std::endl;
    return 0;
}