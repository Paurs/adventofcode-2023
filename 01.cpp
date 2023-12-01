#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

std::vector<std::string> read_input(std::string filename) {
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

std::vector<char> digits{'0','1','2','3','4','5','6','7','8','9'};

int get_calibration_sum(const std::vector<std::string>& input) {
    int sum{0};
    for (const auto& line : input) {
        auto first = std::find_first_of(line.begin(), line.end(), digits.begin(), digits.end());
        auto second = std::find_first_of(line.rbegin(), line.rend(), digits.begin(), digits.end());
        sum += (*first - '0')*10 + *second - '0';
    }
    return sum;
}

std::unordered_map<std::string, std::string> digits_map {
        { "zero", "zero0zero" },
        { "one", "one1one" },
        { "two", "two2two" },
        { "three", "three3three" },
        { "four", "four4four" },
        { "five", "five5five" },
        { "six", "six6six" },
        { "seven", "seven7seven" },
        { "eight", "eight8eight" },
        { "nine", "nine9nine" }, 
};

std::vector<std::string> replace_digits(const std::vector<std::string>& input) {
    std::vector<std::string> new_input;
    for (const auto& line : input) {
        std::string new_line = line;
        for (const auto& [digit, replacement] : digits_map) {
            size_t pos = 0;
            while ((pos = new_line.find(digit, pos)) != std::string::npos) {
                new_line.replace(pos, digit.length(), replacement);
                pos += replacement.length();
            }
        }
        new_input.push_back(new_line);   
    }
    return new_input;
}

int main() {
    auto input{read_input("../01.txt")};
    std::cout << get_calibration_sum(input) << std::endl;
    std::cout << get_calibration_sum(replace_digits(input)) << std::endl;
    
    return 0;
}