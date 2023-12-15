#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

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

std::vector<std::string> parseInput(std::string input){
    std::vector<std::string> sequence;
    std::string temp;
    for(int i = 0; i < input.size(); i++){
        if(input[i] == ','){
            sequence.push_back(temp);
            temp.clear();
        }
        else
            temp += input[i];
    }
    sequence.push_back(temp);
    return sequence;
}

int hash(std::string str){
    int hash{0};  
    for(auto &c : str)
        hash += c, hash *= 17, hash %= 256;
    return hash;
}

int solveOne(std::vector<std::string> input){
    int sum{0};
    for(auto &str : input)
        sum += hash(str);
    return sum;
}

void insertLens(std::vector<std::vector<std::tuple<std::string, int>>> &boxes, std::string str){
    std::tuple<std::string, int> newLens{str.substr(0, str.find("=")), stoi(str.substr(str.find("=") + 1))};
    int hashVal{hash(std::get<0>(newLens))};
    for(auto &lens : boxes[hashVal]){
        if(std::get<0>(lens) == std::get<0>(newLens)){
            std::get<1>(lens) = std::get<1>(newLens);
            return;
        }
    }
    boxes[hashVal].push_back(newLens);
    return;
}

void removeLens(std::vector<std::vector<std::tuple<std::string, int>>> &boxes, std::string str){
    int hashVal{hash(str)};
    for(auto &lens : boxes[hashVal]){
        if(std::get<0>(lens) == str){
            boxes[hashVal].erase(std::find(boxes[hashVal].begin(), boxes[hashVal].end(), lens));
            return;
        }
    }
    return;
}

int solveTwo(std::vector<std::string> input){
    int sum{0};
    std::vector<std::vector<std::tuple<std::string, int>>> boxes(256);

    for(auto &str : input){
        if(str.find("-") != std::string::npos)
            removeLens(boxes, str.substr(0, str.find("-")));
        else
            insertLens(boxes, str);
    }

    for(int i = 0; i < boxes.size(); i++){
        if(boxes[i].empty())
            continue;
        for(int j = 0; j < boxes[i].size(); j++){
            sum += (i+1) * (j+1) * std::get<1>(boxes[i][j]);
        }
    }
    return sum;
}

int main(int argc, char const *argv[]){
    std::vector<std::string> input = parseInput(readInput("../inputs/15.txt")[0]);
    std::cout << "Part 1: " <<  solveOne(input) << std::endl;
    std::cout << "Part 2: " <<  solveTwo(input) << std::endl;
    return 0;
}
