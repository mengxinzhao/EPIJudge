#include <algorithm>
#include <functional>
#include <vector>
#include <random>
#include <iostream>
#include <time.h>
#include <unordered_map>
#include "test_framework/random_sequence_checker.h"
#include "test_framework/test_timer.h"

using std::bind;
using std::sort;
using std::vector;
using std::unordered_map;
using std::random_device;
using std::default_random_engine;

// Assumption: there are at least k elements in the stream.
// https://en.wikipedia.org/wiki/Reservoir_sampling
vector<int> OnlineRandomSample(vector<int>::const_iterator stream_begin,
                               const vector<int>::const_iterator stream_end,
                               int k) {
  vector<int> v(stream_begin, stream_begin+k);

  int stream_size =  std::distance(stream_begin,stream_end);
  default_random_engine generator ((random_device())());
  for (int i=k ; i < stream_size ; i++) {
      std::uniform_int_distribution<int> distribution(0,i);
      int draw = distribution(generator);
      if (draw < k) {
	      // k/(i+1) chance of replacement and  1-k/(i+1)chance of keeping
	      v[draw] = *(stream_begin+i);
      }
  }
  return v;
}

bool OnlineRandomSamplingRunner(TestTimer& timer, vector<int> stream, int k) {
  vector<vector<int>> results;
  timer.Start();
  std::generate_n(
      back_inserter(results), 100000,
      std::bind(OnlineRandomSample, cbegin(stream), cend(stream), k));
  timer.Stop();

  int total_possible_outcomes = BinomialCoefficient(stream.size(), k);
  sort(begin(stream), end(stream));
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(stream.size(), k); ++i) {
    combinations.emplace_back(
        ComputeCombinationIdx(stream, stream.size(), k, i));
  }
  vector<int> sequence;
  for (vector<int> result : results) {
    sort(begin(result), end(result));
    sequence.emplace_back(
        distance(begin(combinations),
                 find(begin(combinations), end(combinations), result)));
  }
  return CheckSequenceIsUniformlyRandom(sequence, total_possible_outcomes,
                                        0.01);
}

void OnlineRandomSampleWrapper(TestTimer& timer, const vector<int>& stream,
                               int k) {
  RunFuncWithRetries(
      bind(OnlineRandomSamplingRunner, std::ref(timer), std::cref(stream), k));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "stream", "k"};
  generic_test_main(argc, argv, param_names, "online_sampling.tsv",
                    &OnlineRandomSampleWrapper);
  return 0;
}
