#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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

void tiltNorth(std::vector<std::string>& input) {
    bool changed{true};
    while(changed) {
        changed = false;
        for(int i = 0 ; i < input.size() - 1; i++) {
            for(int j = 0; j < input[i].size(); j++) {
                if(input[i+1][j] == 'O' && input[i][j] == '.') {
                    input[i+1][j] = '.';
                    input[i][j] = 'O';
                    changed = true;
                }
            }
        }
    }
}

void tiltWest(std::vector<std::string>& input) {
    bool changed{true};
    while(changed) {
        changed = false;
        for(int i = 0 ; i < input.size(); i++) {
            for(int j = 0; j < input[i].size() - 1; j++) {
                if(input[i][j+1] == 'O' && input[i][j] == '.') {
                    input[i][j+1] = '.';
                    input[i][j] = 'O';
                    changed = true;
                }
            }
        }
    }
}

void tiltSouth(std::vector<std::string>& input) {
    bool changed{true};
    while(changed) {
        changed = false;
        for(int i = input.size() - 1 ; i > 0; i--) {
            for(int j = 0; j < input[i].size(); j++) {
                if(input[i-1][j] == 'O' && input[i][j] == '.') {
                    input[i-1][j] = '.';
                    input[i][j] = 'O';
                    changed = true;
                }
            }
        }
    }
}

void tiltEast(std::vector<std::string>& input) {
    bool changed{true};
    while(changed) {
        changed = false;
        for(int i = 0 ; i < input.size(); i++) {
            for(int j = input[i].size() - 1; j > 0; j--) {
                if(input[i][j-1] == 'O' && input[i][j] == '.') {
                    input[i][j-1] = '.';
                    input[i][j] = 'O';
                    changed = true;
                }
            }
        }
    }
}

void cycle(std::vector<std::string>& input) {
    tiltNorth(input);
    tiltWest(input);
    tiltSouth(input);
    tiltEast(input);
}

int calculateLoad(std::vector<std::string> input) {
    int load{0};
    for(int i = 0; i < input.size(); i++) {
        std::string line = input[i];
        int numRocks = std::count(line.begin(), line.end(), 'O');   
        load += (input.size() - i) * numRocks;
    }
    return load;
}

int solveOne(std::vector<std::string> input) {
    tiltNorth(input);
    return calculateLoad(input);
}

int solveTwo(std::vector<std::string> input) {
    std::map<std::vector<std::string>, long> log;
    for(long i = 0; i < 1000000000; i++) {
        if(log.contains(input)){
            long cycleLength = i - log[input];
            long remaining = 1000000000 - i;
            i = 1000000000 - remaining % cycleLength;
            for(i; i < 1000000000; i++)
                cycle(input);
            return calculateLoad(input);
        }
        log[input] = i;
        cycle(input);
    }

    return -1;
}

int main(int argc, char const *argv[]){
    std::cout << "Part 1: " << solveOne(readInput("../inputs/14.txt")) << "\n";
    std::cout << "Part 2: " << solveTwo(readInput("../inputs/14.txt")) << "\n";
    return 0;
}

