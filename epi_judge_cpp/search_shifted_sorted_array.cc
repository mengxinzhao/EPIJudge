#include <vector>

using std::vector;

// not O(logn) solution
int SearchSmallest(const vector<int>& A) {
  // Implement this placeholder.
	for (int i=0; i< A.size()-1;i++) {
		if (A[i] >= A[i+1])
		return i+1;
	}
  return 0;
}

// O(log(n)) solution
int SearchSmallest2(const vector<int>& A) {
	// Implement this placeholder.
	int l =0, r = A.size()-1;  // search range [l,r] till r = l+1. the smallest number is in k=l
	int mid = l +(r -l)/2 ;
	while(l < r){
		int mid = l +(r -l)/2 ;
		if (A[mid] > A[r]) {
			// d d d d     d k d d
			// l      mid        r
			// l  ===>     l     r
			l = mid + 1;
		}else {
			// d d k d d   d d d d d
			// l       mid         r
			// l        r   <====   r
			r = mid;
		}
	}

	return l;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "search_shifted_sorted_array.tsv",
                    &SearchSmallest2);
  return 0;
}
