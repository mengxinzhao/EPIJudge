#include <vector>
#include <algorithm>

using std::vector;

bool HasTwoSum(const vector<int>& A, int t) {
  // Implement this placeholder.
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
  generic_test_main(argc, argv, "two_sum.tsv", &HasTwoSum);
  return 0;
}
