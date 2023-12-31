#include "../include/ver.hpp"
#include "MyPriorityQueue.hpp"
#include "convert.hpp"
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>

namespace {

// As always, this is a STARTING POINT of test cases
// and is not an exhaustive set of test cases.
// You should be sure to test EVERY function of
// your priority queue as well as the Lewis Carroll puzzle.

TEST(Required, SimplePQCreation) {
  MyPriorityQueue<int> mpq;
  mpq.insert(3);
  EXPECT_EQ(mpq.min(), 3);
}

TEST(Required, SimpleTestOfMin) {
  MyPriorityQueue<int> mpq;
  mpq.insert(3);
  mpq.insert(5);
  EXPECT_EQ(mpq.min(), 3);
}

TEST(Required, SimpleTestOfMinUpdating) {
  MyPriorityQueue<int> mpq;
  mpq.insert(3);
  mpq.insert(2);
  EXPECT_EQ(mpq.min(), 2);
}

TEST(RequiredPart2, AntToEat) {
  std::string WORD_ONE = "ant";
  std::string WORD_TWO = "eat";
  auto CORRECT_LENGTH = 5;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(SampleTests, PuttersToHampers) {
  std::string WORD_ONE = "putters";
  std::string WORD_TWO = "hampers";
  auto CORRECT_LENGTH = 14;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(SampleTests, BankingToBrewing) {
  std::string WORD_ONE = "banking";
  std::string WORD_TWO = "brewing";
  auto CORRECT_LENGTH = 15;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(SampleTests, ChangesToGlasses) {
  std::string WORD_ONE = "changes";
  std::string WORD_TWO = "glasses";
  auto CORRECT_LENGTH = 48;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(SampleTests, ChangesToSmashed) {
  std::string WORD_ONE = "changes";
  std::string WORD_TWO = "smashed";
  auto CORRECT_LENGTH = 48;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(SampleTests, BoostedToClasses) {
  std::string WORD_ONE = "boosted";
  std::string WORD_TWO = "classes";
  auto CORRECT_LENGTH = 44;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

// Additional Tests

TEST(Additional1, Insert1) {
  MyPriorityQueue<int> mpq;

  std::vector<int> v;
  for (int i = 0; i < 100000; i++) {
    int r = rand() % 100000;
    v.push_back(r);
    mpq.insert(r);
  }

  std::sort(v.begin(), v.end());

  EXPECT_EQ(mpq.min(), v[0]);

  for (int i = 0; i < 100000; i++) {
    mpq.extractMin();
    v.erase(v.begin());
    if (v.size() > 0) {
      EXPECT_EQ(mpq.min(), v[0]);
    }
  }

  EXPECT_EQ(mpq.size(), 0);

  for (int i = 0; i < 100000; i++) {
    int r = rand() % 100000;
    v.push_back(r);
    mpq.insert(r);
  }

  std::sort(v.begin(), v.end());

  EXPECT_EQ(mpq.min(), v[0]);

  for (int i = 0; i < 100000; i++) {
    mpq.extractMin();
    v.erase(v.begin());
    if (v.size() > 0) {
      EXPECT_EQ(mpq.min(), v[0]);
    }
  }
}

TEST(Additional1, Insert2) {
  // Test case for empty insert and same insert
  MyPriorityQueue<int> mpq;

  mpq.insert(1);
  mpq.insert(1);
  mpq.insert(1);

  EXPECT_EQ(mpq.min(), 1);

  mpq.extractMin();
  mpq.extractMin();
  mpq.extractMin();

  EXPECT_THROW(mpq.min(), PriorityQueueEmptyException);
  EXPECT_THROW(mpq.extractMin(), PriorityQueueEmptyException);

  mpq.insert(1);
  mpq.insert(1);
  mpq.insert(0);
  mpq.insert(342423);

  EXPECT_FALSE(mpq.isEmpty());

  EXPECT_EQ(mpq.min(), 0);

  mpq.extractMin();

  EXPECT_EQ(mpq.min(), 1);

  mpq.extractMin();

  EXPECT_EQ(mpq.min(), 1);

  mpq.extractMin();

  EXPECT_EQ(mpq.min(), 342423);

  mpq.extractMin();

  EXPECT_THROW(mpq.min(), PriorityQueueEmptyException);
  EXPECT_THROW(mpq.extractMin(), PriorityQueueEmptyException);
  EXPECT_EQ(mpq.size(), 0);
  EXPECT_TRUE(mpq.isEmpty());
}

TEST(Additional2, AntToFox) {
  std::string WORD_ONE = "ant";
  std::string WORD_TWO = "fox";
  auto CORRECT_LENGTH = 7;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, AntToFry) {
  std::string WORD_ONE = "ant";
  std::string WORD_TWO = "fry";
  auto CORRECT_LENGTH = 8;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, AntToPot) {
  std::string WORD_ONE = "ant";
  std::string WORD_TWO = "pot";
  auto CORRECT_LENGTH = 6;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, ChangesToPounder) {
  std::string WORD_ONE = "changes";
  std::string WORD_TWO = "pounder";
  auto CORRECT_LENGTH = 12;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, SweetToAloof) {
  std::string WORD_ONE = "sweet";
  std::string WORD_TWO = "aloof";
  auto CORRECT_LENGTH = 0;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, AntToAnt) {
  std::string WORD_ONE = "ant";
  std::string WORD_TWO = "ant";
  auto CORRECT_LENGTH = 0;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, AtToAnt) {
  std::string WORD_ONE = "at";
  std::string WORD_TWO = "ant";
  auto CORRECT_LENGTH = 0;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, ManToApe) {
  std::string WORD_ONE = "man";
  std::string WORD_TWO = "ape";
  auto CORRECT_LENGTH = 6;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, ColdToWarm) {
  std::string WORD_ONE = "cold";
  std::string WORD_TWO = "warm";
  auto CORRECT_LENGTH = 5;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, FoolToSage) {
  std::string WORD_ONE = "fool";
  std::string WORD_TWO = "sage";
  auto CORRECT_LENGTH = 7;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, ElectroencephalogramToNondeterministically) {
  std::string WORD_ONE = "electroencephalogram";
  std::string WORD_TWO = "nondeterministically";
  auto CORRECT_LENGTH = 0;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, AnthropomorphicallyToIncomprehensibility) {
  std::string WORD_ONE = "anthropomorphically";
  std::string WORD_TWO = "incomprehensibility";
  auto CORRECT_LENGTH = 0;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, BoyishToPaunch) {
  std::string WORD_ONE = "boyish";
  std::string WORD_TWO = "paunch";
  auto CORRECT_LENGTH = 0;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, BoyishToPaunch2) {
  std::string WORD_ONE = "boyish";
  std::string WORD_TWO = "paunchw";
  auto CORRECT_LENGTH = 0;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, EmptyToEmpty) {
  std::string WORD_ONE = "";
  std::string WORD_TWO = "";
  auto CORRECT_LENGTH = 0;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_FALSE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, PuttersToHampers) {
  std::string WORD_ONE = "putters";
  std::string WORD_TWO = "hampers";
  auto CORRECT_LENGTH = 14;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, AbedToAcid) {
  std::string WORD_ONE = "abed";
  std::string WORD_TWO = "acid";
  auto CORRECT_LENGTH = 12;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, AbaterToAmuser) {
  std::string WORD_ONE = "abater";
  std::string WORD_TWO = "amuser";
  auto CORRECT_LENGTH = 6;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, AcornsToArisen) {
  std::string WORD_ONE = "acorns";
  std::string WORD_TWO = "arisen";
  auto CORRECT_LENGTH = 19;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, FurryToClean) {
  std::string WORD_ONE = "furry";
  std::string WORD_TWO = "clean";
  auto CORRECT_LENGTH = 21;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, FurryToGleam) {
  std::string WORD_ONE = "furry";
  std::string WORD_TWO = "gleam";
  auto CORRECT_LENGTH = 23;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, FurryToNotch) {
  std::string WORD_ONE = "furry";
  std::string WORD_TWO = "notch";
  auto CORRECT_LENGTH = 21;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, FurryToQuell) {
  std::string WORD_ONE = "furry";
  std::string WORD_TWO = "quell";
  auto CORRECT_LENGTH = 21;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

TEST(Additional2, FusedToGleam) {
  std::string WORD_ONE = "fused";
  std::string WORD_TWO = "gleam";
  auto CORRECT_LENGTH = 21;

  std::unordered_set<std::string> words;
  std::ifstream in("words.txt");
  loadWordsIntoTable(words, in);

  std::vector<std::string> r = convert(WORD_ONE, WORD_TWO, words);

  std::ifstream in2("words.txt");

  EXPECT_EQ(r.size(), CORRECT_LENGTH);
  EXPECT_TRUE(validConversion(r, WORD_ONE, WORD_TWO, in2));
}

} // namespace