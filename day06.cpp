#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  ifstream input("./inputs/day06");

  string timeLine;
  string distanceLine;

  getline(input, timeLine);
  getline(input, distanceLine);

  auto timeIter = timeLine.begin();
  auto distanceIter = distanceLine.begin();

  for (; *timeIter != ' '; ++timeIter) {
  }
  for (; *distanceIter != ' '; ++distanceIter) {
  }

  auto margin = 1;
  while (timeIter != timeLine.end() && distanceIter != distanceLine.end()) {
    for (; *timeIter == ' '; ++timeIter) {
    }
    for (; *distanceIter == ' '; ++distanceIter) {
    }

    int time = 0;
    for (; timeIter != timeLine.end() && *timeIter != ' '; ++timeIter) {
      time = time * 10 + (*timeIter - '0');
    }
    int distance = 0;
    for (; distanceIter != distanceLine.end() && *distanceIter != ' ';
         ++distanceIter) {
      distance = distance * 10 + (*distanceIter - '0');
    }

    auto disc = time * time - 4 * distance;
    if (disc < 0) {
      cout << "race with no way to win" << endl;
      margin = 0;
      break;
    }

    if (disc == 0) {
      if (time % 2 == 0) {
        continue;
      } else {
        cout << "race with no way to win" << endl;
        margin = 0;
        break;
      }
    }

    auto temp = (time - sqrt(disc)) / 2.0;
    auto root1 = ceil(temp);
    if (root1 == temp) {
      root1 += 1;
    }
    temp = (time + sqrt(disc)) / 2.0;
    auto root2 = floor(temp);
    if (root2 == temp) {
      root2 -= 1;
    }

    cout << root1 << " " << root2 << " " << root2 - root1 + 1 << endl;
    margin *= (root2 - root1) + 1;
  }

  cout << margin << endl;
}
