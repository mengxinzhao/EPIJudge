#include <vector>

using std::vector;

int LongestNondecreasingSubsequenceLength(const vector<int>& A) {
  // Implement this placeholder.
  return 0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "longest_nondecreasing_subsequence.tsv",
                    &LongestNondecreasingSubsequenceLength);
  return 0;
}
