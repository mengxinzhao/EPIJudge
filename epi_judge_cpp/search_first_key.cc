#include <vector>

using std::vector;

// log(n) solution
int  SearchFirstOfK_BST(const vector<int> &A, int k) {
	int left = 0, right = A.size()-1, mid = 0;
	while(left<=right) {
		// assume (right-left) will not overflow. The tree is not super huge
		mid = left + (right-left)/2;
		if (A[mid] > k)
            right = mid-1;
        else if (A[mid] == k) {
            if (mid == 0 || A[mid-1]!= A[mid])
                break;
            else
                mid ++;
        }
		else
            left = mid + 1 ;
	}
	if (left > right)
		return -1;

	return mid;

}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {

  std::vector<std::string> param_names{"A", "k"};
  generic_test_main(argc, argv, param_names, "search_first_key.tsv",
                    &SearchFirstOfK);
  return 0;
}
