#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

template <class I> vector<long> read_nums(I begin, I end) {

  auto iter = begin;

  long temp = 0;
  vector<long> seeds;
  while (iter != end) {
    const auto c = *iter;
    if (c == ' ') {
      seeds.push_back(temp);
      temp = 0;
    } else {
      long value = c - '0';
      if (value < 0 || value > 9) {
        cout << "Invalid seed number: " << c << endl;
        throw;
      }

      temp *= 10;
      temp += value;
    }

    iter++;
  }
  seeds.push_back(temp);

  return seeds;
}

int main() {
  ifstream input_stream("inputs/day05");

  if (!input_stream.is_open()) {
    cout << "Unable to open input file" << endl;
    return 1;
  }

  string line;
  getline(input_stream, line);

  auto seeds = read_nums(++find(line.begin(), line.end(), ' '), line.end());

  for (auto s : seeds) {
    cout << s << endl;
  }

  while (getline(input_stream, line)) {
    if (line.empty() || (line[0] < '0' || line[0] > '9')) {
      continue;
    }

    auto nums = read_nums(line.begin(), line.end());

    for (auto i = 0; i < seeds.size(); i++) {
      auto value = seeds[i];
      if (value > nums[1] && value < nums[1] + nums[2]) {
        seeds[i] = value - nums[1] + nums[0];
      }
    }
  }

  cout << *min_element(seeds.begin(), seeds.end()) << endl;
}
