#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

int check(std::vector<int> update, std::map<int, std::vector<int>> rules) {
    std::set passed = {0};
    for(int i = 0; i < update.size(); ++i) {
        for(auto m : rules[update.at(i)]) {
            if(passed.contains(m) ){
                return 0;
            }
        }
        passed.insert(update.at(i));
    }
    return 1;
}

std::vector<int> sortMy(std::vector<int> update, std::map<int, std::vector<int>> rules) {
    std::set passed = {0};
    for(int i = 0; i < update.size(); ++i) {
        for(auto m : rules[update.at(i)]) {
            if(passed.contains(m) ){
                int index;
                auto it = std::find(update.begin(), update.end(), m);
                if(it != update.end()) {
                    index = std::distance(update.begin(), it);
                    //std::cout << "m: "<< m << " index: " << index << std::endl;
                    std::swap(update[i], update[index]);
                }
                return sortMy(update, rules);
            }
        }
        passed.insert(update.at(i));
    }
    return update;
}

int main()
{
    std::ifstream input("../input.txt");
    std::string line;
    std::map<int, std::vector<int>> rules;
    bool updateBlock = false;
    int sumMidRight = 0, sumMidWrong = 0;

    while(std::getline(input, line)) {
        if(updateBlock) {
            std::vector<int> update;
            std::stringstream ss(line);
            std::string token;

            while (std::getline(ss, token, ',')) {
                int num = std::stoi(token);
                update.push_back(num);
            }
            if(check(update, rules)) {
                sumMidRight += update.at((update.size()-1) / 2);
            } else {
                sumMidWrong += sortMy(update, rules).at((update.size()-1) / 2);
            }
        } else {
            if(line.empty()) updateBlock = true;
            int before, after;
            sscanf(line.c_str(), "%d|%d", &before, &after);
            rules[before].push_back(after);
        }
    }


    std::cout << "Sum from right Updates: " << sumMidRight << std::endl;
    std::cout << "Sum from wrong Updates: " << sumMidWrong << std::endl;
    return 0;
}
