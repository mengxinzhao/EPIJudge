#include <vector>
#include <algorithm>

using std::vector;

bool HasTwoSum(const vector<int>& A, int t) {
  // assume the matrix is sorted already
  int i = 0;
  int j = A.size()-1;
  while (i<=j) {
    if (A[i]+A[j] < t)
      i++;
    else if (A[i]+A[j]>t)
      j--;
    else if (A[i]+A[j] == t)
      return true;
  }
  return false;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A", "t"};
  generic_test_main(argc, argv, param_names, "two_sum.tsv", &HasTwoSum);
  return 0;
}
