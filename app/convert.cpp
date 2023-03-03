#include "convert.hpp"
#include "MyPriorityQueue.hpp"
#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

// You should not need to change this function.
void loadWordsIntoTable(std::unordered_set<std::string> &words,
                        std::istream &in) {
  std::string line, word;
  std::stringstream ss;

  while (getline(in, line)) {
    ss.clear();
    ss << line;
    while (ss >> word) {
      words.insert(word);
    }
  }
}

struct Node {
  std::string word;
  unsigned value;
  unsigned lc_distance;

  Node(const std::string &word, unsigned value, unsigned lc_distance)
      : word(word), value(value), lc_distance(lc_distance) {}

  bool operator<(const Node &other) const {
    if (value == other.value) {
      return lc_distance < other.lc_distance;
    }
    return value < other.value;
  }

  bool operator>(const Node &other) const {
    if (value == other.value) {
      return lc_distance > other.lc_distance;
    }
    return value > other.value;
  }
};

std::vector<std::string> convert(const std::string &s1, const std::string &s2,
                                 const std::unordered_set<std::string> &words) {

  if ((s1.size() != s2.size()) || (s1 == s2) || (s1 == "" || s2 == "") ||
      (words.find(s1) == words.end()) || (words.find(s2) == words.end())) {
    return {};
  }

  std::vector<std::string> result;
  std::map<std::string, std::string> map;
  MyPriorityQueue<Node> queue;

  Node node(s1, 0, 0);
  queue.insert(node);
  map[s1] = "";

  while (!queue.isEmpty()) {
    Node node = queue.min();
    queue.extractMin();

    if (node.word == s2) {
      std::string temp = node.word;
      while (temp != "") {
        result.push_back(temp);
        temp = map[temp];
      }

      std::reverse(result.begin(), result.end());

      return result;
    }

    for (int i = 0; i < node.word.size(); i++) {
      for (char c = 'a'; c <= 'z'; c++) {
        std::string temp = node.word;
        temp[i] = c;

        if (words.find(temp) != words.end() && map.find(temp) == map.end()) {
          map[temp] = node.word;

          unsigned lc_distance = node.lc_distance + 1, num_diff = 0;
          for (unsigned j = 0; j < temp.size(); j++) {
            if (temp[j] != s2[j]) {
              num_diff++;
            }
          }

          Node newNode(temp, lc_distance + num_diff, lc_distance);

          queue.insert(newNode);
          map[temp] = node.word;
        }
      }
    }
  }
  return {};
}