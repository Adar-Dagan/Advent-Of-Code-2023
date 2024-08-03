#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

int get_number(string_view str) {
  int result = 0;
  for (const auto c : str) {
    if (c < '0' || c > '9') {
      throw runtime_error("Invalid number");
    }
    result = result * 10 + (c - '0');
  }
  return result;
}

enum type {
  HIGH_CARD,
  ONE_PAIR,
  TWO_PAIR,
  THREE_OF_A_KIND,
  FULL_HOUSE,
  FOUR_OF_A_KIND,
  FIVE_OF_A_KIND,
};

class Hand {
public:
  type type_;
  int cards[5];

  Hand(string value) {
    vector<pair<char, int>> cardsMap{};
    for (const auto c : value) {
      auto it = find_if(cardsMap.begin(), cardsMap.end(),
                        [c](const auto &p) { return p.first == c; });
      if (it == cardsMap.end()) {
        cardsMap.push_back({c, 1});
      } else {
        it->second++;
      }
    }

    sort(cardsMap.begin(), cardsMap.end(),
         [](const auto &a, const auto &b) { return a.second > b.second; });

    switch (cardsMap[0].second) {
    case 5:
      type_ = FIVE_OF_A_KIND;
      break;
    case 4:
      type_ = FOUR_OF_A_KIND;
      break;
    case 3:
      if (cardsMap[1].second == 2) {
        type_ = FULL_HOUSE;
      } else {
        type_ = THREE_OF_A_KIND;
      }
      break;
    case 2:
      if (cardsMap[1].second == 2) {
        type_ = TWO_PAIR;
      } else {
        type_ = ONE_PAIR;
      }
      break;
    case 1:
      type_ = HIGH_CARD;
      break;
    }

    for (int i = 0; i < 5; i++) {
      if (value[i] >= '2' && value[i] <= '9') {
        cards[i] = value[i] - '2';
      } else {
        switch (value[i]) {
        case 'T':
          cards[i] = 8;
          break;
        case 'J':
          cards[i] = 9;
          break;
        case 'Q':
          cards[i] = 10;
          break;
        case 'K':
          cards[i] = 11;
          break;
        case 'A':
          cards[i] = 12;
          break;
        }
      }
    }
  }

  bool operator<(const Hand &other) const {
    if (type_ != other.type_) {
      return type_ < other.type_;
    } else {
      for (int i = 0; i < 5; i++) {
        if (cards[i] != other.cards[i]) {
          return cards[i] < other.cards[i];
        }
      }
      return false;
    }
  }
};

int main() {
  ifstream fin("./inputs/day07");

  string line;
  map<Hand, int> ranks{};
  while (getline(fin, line)) {
    auto hand = Hand(line.substr(0, 5));
    auto bid = get_number(string_view(line).substr(6));

    ranks.insert({hand, bid});
  }

  int rank = 1;
  int total = 0;
  for (const auto &[hand, bid] : ranks) {
    cout << hand.type_ << "\t" << hand.cards[0] << " " << hand.cards[1] << " "
         << hand.cards[2] << " " << hand.cards[3] << " " << hand.cards[4]
         << "\t" << bid << endl;
    total += rank * bid;
    rank++;
  }

  cout << total << endl;
  return 0;
}
