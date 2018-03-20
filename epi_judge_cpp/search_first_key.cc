#include <vector>

using std::vector;

// this is O(n) solution
int SearchFirstOfK(const vector<int>& A, int k) {
	for (int i=0;i<A.size();i++) {
		if (A[i] == k)
			return i;
	}
  return -1;
}
// 0 1 1 4 4 4 5 9 10 10 12 12 14
// search 4
// return 2
// size 13
int  SearchFirstOfK_BST(const vector<int> &A, int k) {
	int left = 0, right = A.size()-1, mid = 0;
	while(left<=right) {
		// assume (right-left) will not overflow. The tree is not super huge
		mid = left + (right-left)/2;
		if (A[mid] > k)
            right = mid-1;
		else if (A[mid] == k)
            break;
		else
            left = mid + 1 ;
	}
	if (left > right)
		return -1;

	//search from [left , mid -1]
	int i = mid-1;
	while(i >=left && A[i] == k )
		i--;
	if (i!=mid-1) // first occurence  on the left side
		return i+1;
	return mid;

}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {

  std::vector<std::string> param_names{"A", "k"};
  generic_test_main(argc, argv, param_names, "search_first_key.tsv",
                    &SearchFirstOfK);
  return 0;
}
