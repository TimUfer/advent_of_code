#include <fstream>
#include <iostream>
#include <regex>

// --- gets the matches from a line ---
std::vector<std::string> getMatches(std::string in, std::vector<std::string> v, bool &myDo) {
    std::regex mulRegex(R"(mul\([1-9][0-9]{0,2},[1-9][0-9]{0,2}\)|do\(\)|don't\(\))");
    std::sregex_iterator search(in.begin(), in.end(), mulRegex);
    std::sregex_iterator end;

    for(std::regex_iterator iter = search; iter != end; ++iter) {
        const std::smatch& smatch = *iter;
        if(smatch.str() == "do()" ) {
            myDo = true;
        } else if(smatch.str() == "don't()") {
            myDo = false;
        } else {
            if(myDo) v.push_back(smatch.str());
        }
    }
    for(const std::string& s : v) {
        std::cout << s << std::endl;
    }
    return v;
}

int main()
{
    std::ifstream file("../input.txt");
    std::string line;
    std::regex numberRegex("[0-9]+");

    std::vector<std::string> matches;
    bool myDo = true;

    std::vector<int> numbers;

    // --- Analyse the File for Matches ---
    while(std::getline(file, line)) {
        matches = getMatches(line, matches, myDo);
    }

    // --- Analyse the Matches ---
    for(auto m : matches) {
        std::sregex_iterator searchNumber(m.begin(), m.end(), numberRegex);
        std::sregex_iterator end;
        for(std::regex_iterator iter = searchNumber; iter != end; ++iter) {
            const std::smatch& smatch = *iter;
            numbers.push_back(stoi(smatch.str()));
        }
    }
    int result = 0;
    for(int i = 0; i < numbers.size(); i+=2) {
        result += numbers[i] * numbers[i+1];
    }
    std::cout << result << std::endl;
    return 0;
}
