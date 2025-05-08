#include <fstream>
#include <iostream>
using namespace std;

int diagonalAndVertical(string conCat, int length) {
  int diagonalCount = 0;
  for (int i = 0; i < conCat.length(); i++) {

    if (conCat[i] == 'X' || conCat[i] == 'S') {
      string tmp = "";
      tmp.push_back(conCat[i]);
      for (int j = 1; j < 4; j++) {
        if(i + length*j >= conCat.length()) break;
        tmp.push_back(conCat[i + length*j]);
      }
      if(tmp == "XMAS" | tmp =="SAMX") diagonalCount++;
    }
  }
  return diagonalCount;
}

int horizontal(string conCat) {
  int horizontalCount = 0;
  for (int i = 0; i < conCat.length(); i++) {
    if (conCat[i] == 'X' || conCat[i] == 'S') {
      string tmp = "";
      tmp.push_back(conCat[i]);
      for (int j = 1; j < 4; j++) {
        tmp.push_back(conCat[i+j]);
      }

      if(tmp == "XMAS" | tmp =="SAMX") horizontalCount++;
    }
  }
  return horizontalCount;
}


int main() {

  string conCat;
  int count = 0;

  ifstream input("../input.txt");
  string line;
  while (getline(input, line)) {
    conCat += line;
    count += horizontal(line);
  }
  cout << line.length();
  for (int i = -1; i < 2; i++) {
    count += diagonalAndVertical(conCat, line.length()+i);
  }
  //count += horizontal(conCat);

  cout << "XMAS appears: " << count << " times" << endl;
  input.close();
  return 0;
}
