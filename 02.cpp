#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
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

std::vector<std::string> splitGame(std::string input) {
    std::vector<std::string> output;
    std::string temp;
    for (int i = 0; i < input.length(); i++) {
        if(input[i] == ';' || input[i] == ':') {
            output.push_back(temp);
            temp = "";
        } else {
            temp += input[i];
        }
    }
    output.push_back(temp);
    return output;
}

std::vector<std::vector<std::string>> getGames(std::vector<std::string> input) {
    std::vector<std::vector<std::string>> games;
    std::for_each(input.begin(), input.end(), [&games](auto& line) { games.push_back(splitGame(line)); });
    return games;
}

std::vector<std::string> splitHand(std::string hand) {
            
        std::vector<std::string> combos;
        std::string temp;
        for (int i = 0; i < hand.length(); i++) {
            if(hand[i] == ',') {
                combos.push_back(temp);
                temp = "";
            } else {
                temp += hand[i];
            }
        }
        combos.push_back(temp);
        return combos;
}

std::tuple<std::string, std::string> splitCombo(std::string combo) {
    std::string first;
    std::string second;
    for (int i = 0; i < combo.length(); i++) {
        if(combo[i] == ' ') {
            first = combo.substr(0, i);
            second = combo.substr(i+1, combo.length());
        }
    }
    return std::make_tuple(first, second);
}

bool isValidOne(std::vector<std::string> game) {
    for(size_t i = 1; i < game.size(); i++) {
        auto combos = splitHand(game[i]);
        for(auto combo : combos) {

            auto comboT = splitCombo(combo);
            std::string color = std::get<1>(comboT);
            int value = std::stoi(std::get<0>(comboT));

            if(color == "red") {
                if(value > 12)
                    return false;
            } else if(color == "green") {
                if(value > 13)
                    return false;
            } else if(color == "blue") {
                if(value > 14)
                    return false;
            }
        }
    }
    return true;
}

std::unordered_map<std::string, int> minValues(std::vector<std::string> game) {
    std::unordered_map<std::string, int> cubes {
        {"red", 0},
        {"green", 0},
        {"blue", 0}
    };

    for(size_t i = 1; i < game.size(); i++) {
        auto combos = splitHand(game[i]);

        for(auto combo : combos) {

            auto comboT = splitCombo(combo);
            std::string color = std::get<1>(comboT);
            int value = std::stoi(std::get<0>(comboT));

            if(color == "red") {
                if(value > cubes["red"])
                    cubes["red"] = value;
            } else if(color == "green") {
                if(value > cubes["green"])
                    cubes["green"] = value;
            } else if(color == "blue") {
                if(value > cubes["blue"])
                    cubes["blue"] = value;
            }
        }
    }
    return cubes;
}

int power(std::unordered_map<std::string, int> cubes) {
    int p = 1;
    std::for_each(cubes.begin(), cubes.end(), [&p](auto& cube) { p *= cube.second; });
    return p;
}

int main(int argc, char const *argv[]) {

    int sum1{0};
    int sum2{0};
    auto games = getGames(readInput("../02.txt"));
    
    for(auto game : games) {  
        if(isValidOne(game)) {

            sum1 += std::stoi(std::get<1>(splitCombo(game[0])));
        }
        sum2 += power(minValues(game));
    }
    
    std::cout << "Part 1: " << sum1 << std::endl;
    std::cout << "Part 2: " << sum2 << std::endl;

}
