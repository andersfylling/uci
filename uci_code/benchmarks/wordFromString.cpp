#include <sstream>
#include "benchmark/benchmark.h"

// loop the string until space is hit
static void BM_stringLoop(benchmark::State& state) {
  std::string str = "uci this text should be completely ignored by the parser.";
  while (state.KeepRunning()) {
    std::string word = "";

    for (auto c : str) {
      if (c == ' ') {
        break;
      }

      word += c;
    }
  }
}

BENCHMARK(BM_stringLoop);

// use stringstream to extract the first word
static void BM_stringStream(benchmark::State& state) {
  std::string str = "uci this text should be completely ignored by the parser.";
  while (state.KeepRunning()) {
    std::string word = "";
    std::stringstream sentence(str);

    sentence >> word;
  }
}

BENCHMARK(BM_stringStream);

// use stringstream to extract the first word, but don't initialize the std::string word var.
static void BM_stringStream2(benchmark::State& state) {
  std::string str = "uci this text should be completely ignored by the parser.";
  while (state.KeepRunning()) {
    std::string word;
    std::stringstream sentence(str);

    sentence >> word;
  }
}

BENCHMARK(BM_stringStream2);


/**
 * Results
 *
 * --------------------------------------------------------
 * Benchmark                 Time           CPU Iterations
 * --------------------------------------------------------
 * BM_stringLoop            54 ns         54 ns   12601129 // winner..
 * BM_stringStream         471 ns        471 ns    1522436
 * BM_stringStream2        449 ns        448 ns    1548188
 */