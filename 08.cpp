#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <tuple>
#include <numeric>

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

std::unordered_map<std::string, std::vector<std::string>> parseNodes(std::vector<std::string> input) {
    std::unordered_map<std::string, std::vector<std::string>> nodes;
    for (auto &line : input) {
        if (line.empty()) {
            continue;
        } else {
            std::string name{line.substr(0,3)};
            std::string left{line.substr(7,3)};
            std::string right{line.substr(12,3)};
            nodes.insert({name, {left, right}});
        }
    }
    return nodes;
}

// From AAA to ZZZ
int walkPath(std::unordered_map<std::string, std::vector<std::string>> nodes, std::string instructions) {
    int count{0};
    int i{0};
    std::string current{"AAA"};

    while(current != "ZZZ") {
        if (instructions[i] == 'L')
            current = nodes[current][0];
        else
            current = nodes[current][1];
        i++;
        if(i == instructions.size())
            i = 0;
        count++;
    }

    return count;
}

// From given node to any node ending in Z
int walkPath(std::unordered_map<std::string, std::vector<std::string>> nodes, std::string instructions, std::string start) {
    int count{0};
    int i{0};
    std::string current{start};

    while(!(current.at(2) == 'Z')) {
        if (instructions[i] == 'L')
            current = nodes[current][0];
        else
            current = nodes[current][1];
        i++;
        if(i == instructions.size())
            i = 0;
        count++;
    }

    return count;
}

long walkSimultaneously(std::unordered_map<std::string, std::vector<std::string>> nodes, std::string instructions) {
    std::vector<std::tuple<std::string, std::vector<std::string >>> startNodes;
    for(auto &node : nodes) {
        if(node.first.at(2) == 'A')
            startNodes.push_back(node);
    }

    std::vector<int> steps;
    for(auto &node : startNodes) 
       steps.push_back(walkPath(nodes, instructions, std::get<0>(node)));

    long lcm{1};
    for(auto &step : steps)
        lcm = std::lcm(lcm, step);

    return lcm;
}


int main(int argc, char const *argv[])
{

    std::vector<std::string> input = readInput("../inputs/08.txt");
    std::string instructions{input[0]};
    input.erase(input.begin());

    std::cout << "Part 1: " << walkPath(parseNodes(input), instructions) << std::endl;
    std::cout << "Part 2: " << walkSimultaneously(parseNodes(input), instructions) << std::endl;

    return 0;
}
