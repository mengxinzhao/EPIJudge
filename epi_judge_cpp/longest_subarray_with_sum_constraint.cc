#include <vector>

using std::vector;

int FindLongestSubarrayLessEqualK(const vector<int>& A, int k) {
  // Implement this placeholder.
  return 0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A", "k"};
  generic_test_main(argc, argv, param_names,
                    "longest_subarray_with_sum_constraint.tsv",
                    &FindLongestSubarrayLessEqualK);
  return 0;
}
