#include <vector>

using std::vector;

int MinimumPathWeight(const vector<vector<int>>& triangle) {
  // Implement this placeholder.
  return 0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"triangle"};
  generic_test_main(argc, argv, param_names,
                    "minimum_weight_path_in_a_triangle.tsv",
                    &MinimumPathWeight);
  return 0;
}
