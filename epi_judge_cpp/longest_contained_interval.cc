#include <vector>

using std::vector;

int LongestContainedRange(const vector<int>& A) {
  // Implement this placeholder.
  return 0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "longest_contained_interval.tsv",
                    &LongestContainedRange);
  return 0;
}
