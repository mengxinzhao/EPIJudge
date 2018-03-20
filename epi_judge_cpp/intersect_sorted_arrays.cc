#include <vector>
#include <cstdlib>
#include <iostream>

using std::vector;
//O(n+m) n,m A,B's length
vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  vector<int> val;
	size_t i=0,j=0;
	while (i < A.size() && j<B.size()) {
		if (A[i]==B[j] ) {
			 if ( val.empty() || val.back()!=A[i])  {
				// no duplicates
				 val.push_back(A[i]);
			}
 			// increase
			i++;
			j++;
		}else if (A[i] > B[j]) {
			j++;
		}else
			i++;
	}

	return val;

}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A", "B"};
  generic_test_main(argc, argv, param_names, "intersect_sorted_arrays.tsv",
                    &IntersectTwoSortedArrays);
  return 0;
}
