#include <fstream>
#include <iostream>

int calcTotalDistance(std::vector<int> v1, std::vector<int> v2) {
    int sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        int temp = 0;
        if (v1[i] > v2[i]) {
            temp = v1[i] - v2[i];
        } else {
            temp = v2[i] - v1[i];
        }
        sum += temp;
    }
    return sum;
}

int clacSimilarityScore(std::vector<int> v1, std::vector<int> v2) {
    int simScore = 0;
    for (int i = 0; i < v1.size(); i++) {
        int count = 0;
        int prev = 0;
        for (int j = 0; j < v2.size(); j++) {
            if(v1[i] == v2[j]) {
                prev = v2[j];
                ++count;
            } else if(prev == v1[i] && v2[j] != v1[i]) {
                break;
            }
        }
        simScore += v1[i] * count;
    }
    return simScore;
}

int main()
{
    std::vector<int> v1;
    std::vector<int> v2;
    std::ifstream input("../input.txt");
    std::string line;
    while (getline (input, line)) {
        int a;
        int b;
        sscanf(line.c_str(), "%d %d", &a, &b);
        v1.push_back(a);
        v2.push_back(b);
    }
    std::ranges::sort(v1);
    std::ranges::sort(v2);

    std::cout << "Total Distance: " << calcTotalDistance(v1, v2) << std::endl;
    std::cout << "Similarity Score : " << clacSimilarityScore(v1, v2) << std::endl;

    return 0;
}
