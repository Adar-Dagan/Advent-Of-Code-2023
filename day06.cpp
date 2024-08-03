#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

template <class InputIt> constexpr InputIt goToStart(InputIt it, InputIt end) {
  auto firstSpace = find(it, end, ' ');
  return find_if_not(firstSpace, end, [](char c) { return c == ' '; });
}

auto get_number(const string &s) {
  auto firstSpace = find(s.begin(), s.end(), ' ');
  auto numberStart =
      find_if_not(firstSpace, s.end(), [](char c) { return c == ' '; });

  long long value = 0;
  for_each(numberStart, s.end(), [&value](const auto c) {
    if (c != ' ') {
      value = value * 10 + (c - '0');
    }
  });
  return value;
}

int main() {
  ifstream input("./inputs/day06");

  string timeLine;
  string distanceLine;

  getline(input, timeLine);
  getline(input, distanceLine);

  auto time = get_number(timeLine);
  auto distance = get_number(distanceLine);

  cout << time << " " << distance << endl;

  auto disc = time * time - 4 * distance;
  if (disc < 0) {
    cout << "race with no way to win" << endl;
    return 1;
  }

  if (disc == 0) {
    if (time % 2 == 0) {
      cout << 1 << endl;
      return 0;
    } else {
      cout << "race with no way to win" << endl;
      return 1;
    }
  }

  auto discSqrt = sqrt(disc);
  auto temp = (time - discSqrt) / 2.0;
  auto root1 = ceil(temp);
  if (root1 == temp) {
    root1 += 1;
  }
  temp = (time + discSqrt) / 2.0;
  auto root2 = floor(temp);
  if (root2 == temp) {
    root2 -= 1;
  }

  auto margin = (root2 - root1) + 1;
  cout << root1 << " " << root2 << endl;

  cout << setprecision(10) << margin << endl;

  return 0;
}
