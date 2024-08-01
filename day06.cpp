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
  for (; *timeIter == ' '; ++timeIter) {
  }
  for (; *distanceIter == ' '; ++distanceIter) {
  }

  auto margin = 1;

  long long time = 0;
  for (; timeIter != timeLine.end(); ++timeIter) {
    if (*timeIter == ' ') {
      continue;
    }
    time = time * 10 + (*timeIter - '0');
  }
  long long distance = 0;
  for (; distanceIter != distanceLine.end(); ++distanceIter) {
    if (*distanceIter == ' ') {
      continue;
    }
    distance = distance * 10 + (*distanceIter - '0');
  }

  auto disc = time * time - 4 * distance;
  cout << disc << endl;
  if (disc < 0) {
    cout << "race with no way to win" << endl;
    margin = 0;
    return 1;
  }

  if (disc == 0) {
    if (time % 2 == 0) {
      return 1;
    } else {
      cout << "race with no way to win" << endl;
      margin = 0;
      return 1;
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

  cout << margin << endl;
}
