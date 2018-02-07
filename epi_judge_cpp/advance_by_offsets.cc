#include <vector>
#include <iostream>

using std::vector;

bool reachable(int i, int j,vector<int> max_advance_steps ) {
	// i = start, j = end
	if (i==j) return true;

	// jump forward
	if ((j>i) && max_advance_steps[i]>=0 &&  max_advance_steps[i] >=j-i)
		return true;
	// jump backward
	if ((j<i) && max_advance_steps[i] < 0 && max_advance_steps[i] < j - i)
		return true;

	// if reachable using an intermediate  node
	for (int step = 1; step <=max_advance_steps[i];step++)
		if (reachable(i,i+step, max_advance_steps) && reachable(i+step,j,max_advance_steps) == true)
			return true;
	return false;
}
bool CanReachEnd(const vector<int>& max_advance_steps) {
	// Implement this placeholder.
	// 0, minus numbers might be present

	return reachable(0, max_advance_steps.size()-1, max_advance_steps);

}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"max_advance_steps"};
  generic_test_main(argc, argv, param_names, "advance_by_offsets.tsv",
                    &CanReachEnd);
  return 0;
}
