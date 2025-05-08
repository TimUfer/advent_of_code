#include <fstream>
#include <iostream>
#include <sstream>

int checkSafeRow(std::vector<int> row) {
    short safe = 0;
    short decrease = 99; // 99 = null, 1 = decrease, 2 = increase
    for (int i = 0; i < row.size()-1; i++) {
        if(row[i] > row[i+1]) {
            if(decrease != 1 && decrease < 99) {
                safe = 0;
                break;

            }
            if(abs(row[i] - row[i+1]) < 1 | abs(row[i] - row[i+1]) > 3) {
                safe = 0;
                break;
            }
            decrease = 1;
            safe = 1;
        } else if(row[i] < row[i+1]) {
            if(decrease != 2 && decrease < 99) {
                safe = 0;
                break;
            }
            if(abs(row[i] - row[i+1]) < 1 | abs(row[i] - row[i+1]) > 3) {
                safe = 0;
                break;
            }
            decrease = 2;
            safe = 1;
        } else if(row[i] == row[i+1]) {

            safe = 0;
            break;

        }
    }
    return safe;
}

int checkSafeWithDampner(std::vector<int> row) {
    int safe = 0;
    safe = checkSafeRow(row);

    for (int i = 0; i < row.size(); i++) {
        std::vector<int> tmp = row;
        tmp.erase(tmp.begin()+i);
        safe += checkSafeRow(tmp);
    }
    if(safe >= 1) {
        return 1;
    }
    return 0;
}

int main() {
    int count = 0;
    int countWithoutDampner = 0;
    std::ifstream input("../input.txt");
    std::string line;
    while(getline(input, line)) {
        std::istringstream iss(line);
        int element;
        std::vector<int> row;
        while (iss >> element) {
            //std::cout << element << " ";
            row.push_back(element);
        }
        int withDampner = checkSafeWithDampner(row);
        int withoutDampner = checkSafeRow(row);
        countWithoutDampner += withoutDampner;
        count += withDampner;
        /*std::cout << std::endl;
        std::cout << "Safe? 1 = Yes   2 = No : " << withDampner << std::endl;
        std::cout << std::endl;*/

    }
    std::cout << std::endl;
    std::cout << "How many are Safe Part 1: " << countWithoutDampner << std::endl;
    std::cout << "How many are Safe Part 2: " << count << std::endl;

    return 0;
}
