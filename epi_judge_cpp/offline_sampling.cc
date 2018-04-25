#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>
#include <random>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#include "test_framework/random_sequence_checker.h"
#include "test_framework/test_timer.h"

using std::bind;
using std::vector;

void RandomSampling(int k, vector<int>* A_ptr) {
  vector<int> &v = *A_ptr;
  int size = v.size();
  std::default_random_engine generator (time(0));
  for (int i=0; i < k;i++) {
     std::uniform_int_distribution<int> distribution(i,v.size()-1);
     int draw = distribution(generator);
     std::swap(v[i],v[draw]);
  }
	// only return k elements
	v.resize(k);
  return ;
}

bool RandomSamplingRunner(TestTimer& timer, int k, vector<int> A) {
  vector<vector<int>> results;
  timer.Start();
  for (int i = 0; i < 100000; ++i) {
    RandomSampling(k, &A);
    results.emplace_back(begin(A), begin(A) + k);
  }
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

void RandomSamplingWrapper(TestTimer& timer, int k, const vector<int>& A) {
  RunFuncWithRetries(
      bind(RandomSamplingRunner, std::ref(timer), k, std::cref(A)));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "k", "A"};
  generic_test_main(argc, argv, param_names, "offline_sampling.tsv",
                    &RandomSamplingWrapper);
  return 0;
}
