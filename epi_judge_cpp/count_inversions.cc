#include <vector>
#include <iostream>
using std::vector;

int countInversions(vector<int> &A, int left, int right) {
	if (left >= right)
		return 0;

	int mid = (left + right)/2;   // assume there is no overflow
	return countInversions(A,left,mid) + countInversions(A,mid+1,right) + ((A[mid] > A[mid+1])?1:0);
}



int CountInversions(vector<int> A) {
  // Implement this placeholder.

	//total inversion number = count(0,mid) + count(mid+1,end) + count(mid, mid+1);
	int result = countInversions(A,0,A.size()-1);
  return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "count_inversions.tsv",
                    &CountInversions);
  return 0;
}
