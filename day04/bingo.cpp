#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <array>

using namespace std;

// void parse_line(string line, vector<int> numbers) {
//     size_t* space_pos;
//     while(space_pos != line.end()) {
//         numbers.push_back(std::stoi(line, space_pos, 10));
//         line = line.substr(space_pos);
//     }
// }
struct row {
    std::vector<int> numbers;
    int sum = 0;
};

template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = std::stoi(item, nullptr, 10);
    }
}

std::vector<int> split(const std::string &s, char delim) {
    std::vector<int> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

//typedef std:array<std::array<int,5>, 5> plutt;

bool is_win(std::array<std::array<int,5>, 5>& board) {
    int column = 0;
    int row = 0;
    int marked_in_a_row = 0;
    bool winner_found = false;
    for(int column = 0; column < 5; ++column) {
        marked_in_a_row = 0;
        for(int row = 0; row < 5; ++row) {
            if(board[column][row] == -1)
                marked_in_a_row++;
            if(marked_in_a_row == 5) {
                winner_found = true;
                goto after_loop;
            }
        }
    }
    for(int row = 0; row < 5; ++row) {
        marked_in_a_row = 0;
        for(int column = 0; column < 5; ++column) {
            if(board[column][row] == -1)
                marked_in_a_row++;
            if(marked_in_a_row == 5) {
                winner_found = true;
                goto after_loop;
            }
        }
    }
after_loop:
    return winner_found;
}

int calculate_sum(std::array<std::array<int,5>, 5>& board) {
    int sum = 0;
    for(int column = 0; column < 5; ++column) {
        for(int row = 0; row < 5; ++row) {
            if(board[column][row] != -1)
                sum += board[column][row];
        }
    }
    return sum;
}

int play(std::vector<int>& draws, std::vector<std::array<std::array<int,5>, 5>>& boards) {
    int column = 0;
    int row = 0;
    int score = 0;
    for(auto draw : draws) {
        for(auto& board : boards) {
            for(int column = 0; column < 5; ++column) {
                for(int row = 0; row < 5; ++row) {
                    if(board[column][row] == draw) {
                        board[column][row] = -1;
                        if(is_win(board)) {
                            score = draw * calculate_sum(board);
                            std::cout<<"Winner found " << score << std::endl;
                            goto winner_found;
                        }
                    }
                }
            }
        }
    }
winner_found:
    return score;
}

int play2(std::vector<int>& draws, std::vector<std::array<std::array<int,5>, 5>>& boards) {
    int column = 0;
    int row = 0;
    int score = 0;
    int boards_with_bingo = 0;
    int index = 0;
    std::vector<bool> winners(boards.size(), false);
    for(auto draw : draws) {
        for(auto& board : boards) {
            index++;
            for(int column = 0; column < 5; ++column) {
                for(int row = 0; row < 5; ++row) {
                    if(board[column][row] == draw) {
                        board[column][row] = -1;
                        if(is_win(board)) {
                            if(winners[index] == true) {
                                continue;
                            }
                            else {                            
                                boards_with_bingo++;
                                winners[index] = true;
                                if(boards_with_bingo == boards.size()) {
                                    score = draw * calculate_sum(board);
                                    goto after_loop;
                                }
                            }
                        }
                    }
                }
            }
        }
        index = 0;
    }

after_loop:
    std::cout<<"Winner found " << score << std::endl;

    return score;
}


int main() {
//     ifstream input_file("input");
//     string line;
//     string draws_string;
//     vector<row> rows;
//     getline(input_file, draws_string);
//     while(getline(input_file, line)) {
//         if(line == "")
//             continue;
//         else {
//             row tmp_row;
//             std::istringstream iss(line);
//             string item;
//             while (std::getline(iss, item, ' ')) {
//                 if(!item.empty()) {
//                     int number = std::stoi(item, nullptr, 10);
//                     tmp_row.numbers.push_back(number);
//                     tmp_row.sum += number;
//                 }
//             }
//             rows.push_back(tmp_row);
//         }
//     }

//     int size = rows.size();
//     for(int row_index = 0; row_index < size; row_index += 5) {
//         for(int num_index = 0; num_index < 5; ++num_index) {
//             row tmp_row;
//             for(int row_subindex = 0; row_subindex < 5; ++row_subindex) {
//                 int number = rows[row_index + row_subindex].numbers[num_index];
//                 tmp_row.numbers.push_back(number);
//                 tmp_row.sum += number;
//                 //std::cout << number << std::endl;
//             }
//             rows.push_back(tmp_row);
//         }
//     }

//     std::vector<int> draws;
//     std::istringstream drawsss(draws_string);
//     string item;
//     while (std::getline(drawsss, item, ',')) {
//         if(!item.empty()) {
//             int number = std::stoi(item, nullptr, 10);
//             draws.push_back(number);
//         }
//     }

//     for(auto draw : draws) {
//         for(auto& row : rows) {
//             auto it = std::find(row.numbers.begin(), row.numbers.end(), draw);
//             if(it != row.numbers.end()) {
//                 row.numbers.erase(it);
//             }
//         }
//         for(auto row : rows) {
//             if(row.numbers.empty()) {
//                 std::cout << row.sum * draw << std::endl;
//                 goto found;
//             }
//         }
//     }
// found:
//     std::cout << "Hej" << std::endl;
    //int board[5][5];
    std::array<std::array<int, 5>, 5> board;

    std::vector<std::array<std::array<int, 5>, 5> > boards;

    ifstream input_file("input");
    string line;
    string draws_string;
    string empty_line;
    getline(input_file, draws_string);
    getline(input_file, empty_line);
    int row = 0;
    int column = 0;
    while(getline(input_file, line)) {
        if(line == "") {
            row = 0;
        }
        else {
            std::istringstream iss(line);
            string item;
            while (std::getline(iss, item, ' ')) {
                if(!item.empty()) {
                    board[column][row] = std::stoi(item);
                    if(column == 4 && row == 4)
                        boards.push_back(board);
                    column++;
                }
            }
            column = 0;
            row++;
        }
    }

    std::vector<int> draws;
    std::istringstream drawsss(draws_string);
    string item;
    while (std::getline(drawsss, item, ',')) {
        if(!item.empty()) {
            int number = std::stoi(item, nullptr, 10);
            draws.push_back(number);
        }
    }

    std::cout << play2(draws, boards) << std::endl;

    return 0;
}