#include <deque>
#include <vector>

using std::deque;
using std::vector;

int MaxSquareSubmatrix(const vector<deque<bool>>& A) {
  // Implement this placeholder.
  return 0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "max_square_submatrix.tsv",
                    &MaxSquareSubmatrix);
  return 0;
}
