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

// Assumption: there are at least k elements in the stream.
// https://en.wikipedia.org/wiki/Reservoir_sampling
vector<int> OnlineRandomSample(vector<int>::const_iterator stream_begin,
                               const vector<int>::const_iterator stream_end,
                               int k) {
  // Implement this placeholder.
  vector<int> v(stream_begin, stream_begin+k);

  int stream_size =  std::distance(stream_begin,stream_end);
  //std::cout<<"size : "<<stream_size << std::endl;
  std::default_random_engine generator (time(0));
  for (int i=k ; i < stream_size ; i++) {
	  //std::uniform_int_distribution<int> distribution(0,i);
      //int draw = distribution(generator);
      //uniform distribution here doesn't pass the judge. why? need to use random number generation
	  int draw = rand() % (i+1);
      if (draw < k) {
	      // k/(i+1) of replacement 1-k/(i+1) of keeping
	      v[draw] = *(stream_begin+i);
      }
  }
  return v;
}

bool OnlineRandomSamplingRunner(TestTimer& timer, vector<int> A, int k) {
  vector<vector<int>> results;
  timer.Start();
  std::generate_n(back_inserter(results), 100000,
                  std::bind(OnlineRandomSample, cbegin(A), cend(A), k));
  timer.Stop();

  int total_possible_outcomes = BinomialCoefficient(A.size(), k);
  sort(begin(A), end(A));
  vector<vector<int>> combinations;
  for (int i = 0; i < BinomialCoefficient(A.size(), k); ++i) {
    combinations.emplace_back(ComputeCombinationIdx(A, A.size(), k, i));
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

void OnlineRandomSampleWrapper(TestTimer& timer, const vector<int>& A, int k) {
  RunFuncWithRetries(
      bind(OnlineRandomSamplingRunner, std::ref(timer), std::cref(A), k));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "online_sampling.tsv",
                    &OnlineRandomSampleWrapper);
  return 0;
}
