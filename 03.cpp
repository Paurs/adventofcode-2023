#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>

const std::vector<std::tuple<int, int>> surounding{
    {-1, -1},
    {0, -1},
    {1, -1},
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0}
};

std::vector<std::string> readInput(std::string filename) {
    std::vector<std::string> input;

    std::ifstream file;
    file.open(filename);
    if(!file) {
        throw std::runtime_error("Could not open file " + filename);
    }

    while (!file.eof()) {
        std::string line;
        std::getline(file, line);
        if(line.empty())
            continue;
        else
            input.push_back(line);
    }
    return input;
}

std::vector<std::tuple<int, std::vector<std::tuple<int, int>>>> getNumbers(std::vector<std::string> input) {
    std::vector<std::tuple<int, std::vector<std::tuple<int, int>>>> numbers;

    bool readingNum{false};
    std::string numString{""};
    std::vector<std::tuple<int,int>> pos;

    for(size_t i = 0; i < input.size(); i++) {
    
        for(size_t j = 0; j < input[i].size(); j++) {
            if(isdigit(input[i][j])) {           
                readingNum = true;
                numString += input[i][j];
                pos.push_back(std::tuple<int, int>(i, j));
            }
            if(!isdigit(input[i][j]) && readingNum) {   
                readingNum = false;
                if(!numString.empty()){
                    numbers.push_back(std::tuple<int, std::vector<std::tuple<int, int>>>(std::stoi(numString), pos));
                    numString.clear();
                    pos.clear();
                } 
            }
        }
        if(!numString.empty()){
            numbers.push_back(std::tuple<int, std::vector<std::tuple<int, int>>>(std::stoi(numString), pos));
            numString.clear();
            pos.clear();
        }
    }

    return numbers;
}


bool isAdjacent(int i, int j, const std::vector<std::string> &input){

    int n = input.size();
    int m = input[i].size();

    for (int k = 0; k < 8; k++){
        if (i + std::get<0>(surounding[k]) < 0 || i + std::get<0>(surounding[k]) >= n || j + std::get<1>(surounding[k]) < 0 || j + std::get<1>(surounding[k]) >= m)
            continue;
        char c = input[i + std::get<0>(surounding[k])][j + std::get<1>(surounding[k])];
        if (!isdigit(c) && c != '.')
            return true;
    }

    return false;
}

auto solveOne(const std::vector<std::string> &input) {
    int sum{0};

    auto numbers = getNumbers(input);
    for(auto &n : numbers) {
        for(auto &p : std::get<1>(n)) {
            if(isAdjacent(std::get<0>(p), std::get<1>(p), input)){
                sum += std::get<0>(n);
                break;
            }
        }
    }

    return sum;
}

std::vector<std::tuple<int, int>> getStars(std::vector<std::string> input) {
    std::vector<std::tuple<int, int>> stars;

    for(size_t i = 0; i < input.size(); i++) {  
        for(size_t j = 0; j < input[i].size(); j++) {
            if(input[i][j] == '*') {         
                stars.push_back(std::tuple<int, int>(i, j));
            }
        }
    }
    return stars;
}

std::tuple<int,int> distance(std::tuple<int, int> a, std::tuple<int, int> b) {
    return std::tuple<int, int>(std::abs(std::get<0>(a) - std::get<0>(b)), std::abs(std::get<1>(a) - std::get<1>(b)));
}

int distance(int a, int b) {
    return std::abs(a - b);
}

bool isGear(std::tuple<int, int> star, std::vector<std::tuple<int, std::vector<std::tuple<int, int>>>> numbers, std::vector<int> &adjacentNumbers) {
 
    for(auto &n : numbers) {
        for(auto &p : std::get<1>(n)) {
            if(std::get<0>(distance(star, p)) <= 1 && std::get<1>(distance(star, p)) <= 1) {
                adjacentNumbers.push_back(std::get<0>(n));
                break;
            }
        }
    }

    if(adjacentNumbers.size() == 2)
        return true;

    return false;
}

auto solveTwo(const std::vector<std::string> &input) {
    int sum{0};

    auto numbers = getNumbers(input);
    auto stars = getStars(input);
    for(auto &s : stars) {
        std::vector<int> adjacentNumbers;
        if(isGear(s, numbers, adjacentNumbers)){
            sum += adjacentNumbers[0] * adjacentNumbers[1];
            adjacentNumbers.clear();
        } 
    }

    return sum;
}



int main(int argc, char const *argv[])
{
    std::cout << "Part 1: " << solveOne(readInput("../inputs/03.txt")) << std::endl;
    std::cout << "Part 2: " << solveTwo(readInput("../inputs/03.txt")) << std::endl;
    return 0;
}
