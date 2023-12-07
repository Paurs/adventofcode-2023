#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <sstream>

struct card {
    std::unordered_set<int> winning;
    std::unordered_set<int> have;
    int points{0};
    int numberMatches{0};
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

card parseCard(std::string input) {
    card newCard;
    newCard.have = std::unordered_set<int>();
    newCard.winning = std::unordered_set<int>();
    
    std::stringstream ss(input);
    bool pipe{false};
    std::string temp;
    int found;
    while (!ss.eof()) {
        ss >> temp;
        if (std::stringstream(temp) >> found)
            if(!pipe)
                newCard.winning.insert(found);
            else
                newCard.have.insert(found);
        else
            pipe = true;
        temp = "";
    }

    for(auto& i : newCard.winning)
        if(newCard.have.find(i) != newCard.have.end()) {
            if(newCard.points == 0)
                newCard.points = 1;
            else
                newCard.points *= 2;
            newCard.numberMatches++;
        }
    
    return newCard;
}

std::vector<card> parseCards(std::vector<std::string> input) {
    std::vector<card> cards;

    std::string prefix{"Card xxx: "};
    for(auto& line : input) {
        if(line.empty())
            continue;
        std::string card{line.substr(prefix.size())};
        cards.push_back(parseCard(card));
    }

    return cards;
}

int solveOne(const std::vector<std::string>& input) {
    int sum{0};
    std::vector<card> cards = parseCards(input);
    
    std::for_each(cards.begin(), cards.end(), [&sum](card& c) { sum += c.points; });

    return sum;
}

int solveTwo(const std::vector<std::string>& input) {
    int numberOfCars{0};
    std::vector<card> cards = parseCards(input);
    std::vector<int> numberCards(cards.size(), 1);

    for(int i = 0; i < cards.size(); i++) {
        for(int j = 1; j <= cards[i].numberMatches; j++) {
            numberCards[i+j] += numberCards[i];
        } 
    }

    std::for_each(numberCards.begin(), numberCards.end(), [&numberOfCars](int& c) { numberOfCars += c; });

    return numberOfCars;
}
    
int main(int argc, char const *argv[])
{
    std::cout << "Part 1: " << solveOne(readInput("../inputs/04.txt")) << std::endl;
    std::cout << "Part 2: " << solveTwo(readInput("../inputs/04.txt")) << std::endl;
    return 0;
}
