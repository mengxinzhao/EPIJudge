
int SquareRoot(int k) {
  // Implement this placeholder.
	if (k<=1) return k;
	if (k<4) return 1;
	if (k>=4 && k<9 ) return 2;

	//upper bound of number to try k/2 * k/2 - k > 0 == > k needs to be > 4
	// for while (l+1 < r) to work at min l = 1  r needs to be >=3
	int l = 1, r = k/2;
	int mid;
	while (l+1 < r) {
		mid = l + (r-l)/2;
		if (k/mid < mid ) // k < mid^2
			r = mid;  // can't go r = mid -1 because the comparasion is  k vs mid^2. need to move slowly
		else if (k/mid == mid )
			return mid;
		else if ( k/mid >mid ) // k > mid^2
			l = mid;
	}

	return l;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"k"};
  generic_test_main(argc, argv, param_names, "int_square_root.tsv",
                    &SquareRoot);
  return 0;
}
