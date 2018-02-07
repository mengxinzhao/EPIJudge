#include <functional>
#include <vector>
#include <algorithm>
#include <random>

#include "test_framework/random_sequence_checker.h"
#include "test_framework/test_timer.h"

using std::bind;
using std::vector;


vector<int> ComputeRandomPermutation(int n) {
  // Implement this placeholder.
	vector <int > v(n,0);

	for (int i=0; i < n; i++)
		v[i] = i;
	//randomly generate 0,n-1 numbers
	std::default_random_engine generator (time(0));
	for (int i=0; i < n;i++) {
		std::uniform_int_distribution<int> distribution(i,v.size()-1);
		int draw = distribution(generator);
		std::swap(v[i],v[draw]);
	}

   return v;
}

int Factorial(int n) { return n <= 1 ? 1 : n * Factorial(n - 1); }

int PermutationIndex(vector<int> perm) {
  int idx = 0;
  int n = perm.size();
  for (int i = 0; i < perm.size(); ++i) {
    int a = perm[i];
    idx += a * Factorial(n - 1);
    for (int j = i + 1; j < perm.size(); ++j) {
      if (perm[j] > a) {
        --perm[j];
      }
    }
    --n;
  }
  return idx;
}

bool ComputeRandomPermutationRunner(TestTimer& timer, int n) {
  vector<vector<int>> results;
  timer.Start();
  for (int i = 0; i < 1000000; ++i) {
    results.emplace_back(ComputeRandomPermutation(n));
  }
  timer.Stop();

  vector<int> sequence;
  for (const vector<int>& result : results) {
    sequence.emplace_back(PermutationIndex(result));
  }
  return CheckSequenceIsUniformlyRandom(sequence, Factorial(n), 0.01);
}

void ComputeRandomPermutationWrapper(TestTimer& timer, int n) {
  RunFuncWithRetries(
      std::bind(ComputeRandomPermutationRunner, std::ref(timer), n));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "n"};
  generic_test_main(argc, argv, param_names, "random_permutation.tsv",
                    &ComputeRandomPermutationWrapper);
  return 0;
}
