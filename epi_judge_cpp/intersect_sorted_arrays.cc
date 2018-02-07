#include <vector>
#include <cstdlib>
#include <iostream>

using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  // Implement this placeholder.
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
  generic_test_main(argc, argv, "intersect_sorted_arrays.tsv",
                    &IntersectTwoSortedArrays);
  return 0;
}
