#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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

std::vector<int> parseRow(std::string row) {
    std::vector<int> parsedRow;
    
    std::stringstream ss(row);
    std::string temp;
    int found;
    while (!ss.eof()) {
        ss >> temp;
        if (std::stringstream(temp) >> found)
            parsedRow.push_back(found);
        temp = "";
    }

    return parsedRow;
}

bool onlyZeros(std::vector<int> row) {
    for(auto &i : row)
        if(i != 0)
            return false;
    return true;
}

int extrapolateNext(std::vector<int> row) {
    std::vector<std::vector<int>> rows;
    std::vector<int> currentRow{row};
    while(!onlyZeros(currentRow)) {
        std::vector<int> nextRow;
        for(int i = 0; i < currentRow.size() - 1; i++) {
            nextRow.push_back(currentRow[i+1] - currentRow[i]);
        }
        rows.push_back(currentRow);
        currentRow = nextRow;
        nextRow.clear();
    }
    rows.push_back(currentRow);

    for(int i = int(rows.size())-1; i > 0; i--)
        rows[i-1].push_back(rows[i-1].at(rows[i-1].size() - 1) + rows[i].at(rows[i].size() - 1));

    return rows[0].at(rows[0].size() - 1);
}

int extrapolateBack(std::vector<int> row) {
    std::vector<std::vector<int>> rows;
    std::vector<int> currentRow{row};

    while(!onlyZeros(currentRow)) {
        std::vector<int> nextRow;
        for(int i = int(currentRow.size())-1; i > 0; i--) {
            nextRow.insert(nextRow.begin(), currentRow[i] - currentRow[i-1]);
        }
        rows.push_back(currentRow);
        currentRow = nextRow;
        nextRow.clear();
    }
    
    for(int i = int(rows.size())-1; i > 0; i--)
        rows[i-1].insert(rows[i-1].begin(), rows[i-1].at(0) - rows[i].at(0));
    
    return rows[0].at(0);
}

int solveOne(std::vector<std::string> input) {
    int sum{0};
    for(auto &line : input) {
        std::vector<int> intRow{parseRow(line)};
        sum += extrapolateNext(intRow);
    }
    return sum;
}

int solveTwo(std::vector<std::string> input) {
    int sum{0};
    for(auto &line : input) {
        std::vector<int> intRow{parseRow(line)};
        sum += extrapolateBack(intRow);
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    std::cout << "Part 1: " << solveOne(readInput("../inputs/09.txt")) << std::endl;
    std::cout << "Part 2: " << solveTwo(readInput("../inputs/09.txt")) << std::endl;
    return 0;
}
