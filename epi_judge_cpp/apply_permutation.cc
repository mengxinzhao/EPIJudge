#include <vector>

using std::vector;

void ApplyPermutation1(vector<int>* perm_ptr, vector<int>* A_ptr) {
	//not an efficient solution. Using extra room here to keep the copy
    vector<int> &v_a = *A_ptr;
	vector<int > copy(v_a);
    vector<int> &v_p = *perm_ptr;
  for (int i=0 ; i < v_p.size();i++)
		v_a[v_p[i]] = copy[i];

  return;
}

//O(n) run time complexity
// constant space
void ApplyPermutation2(vector<int>* perm_ptr, vector<int>* A_ptr) {
	// no extra room
	vector<int> &v_a = *A_ptr;
	vector<int> &v_p = *perm_ptr;
	for (int i=0 ; i < v_p.size();){
		int last_idx = i;
		int curr_val = v_a[i];
		int curr_idx = v_p[i];
		int next_val = INT_MIN;
		int next_idx = INT_MIN;
		while(curr_idx!=INT_MIN) {
			// chain reaction to put all numbers in the right place
			last_idx = curr_idx;
			next_val = v_a[curr_idx]; // save the nodes that is going to be written by permutation
			next_idx = v_p[curr_idx];
			v_a[curr_idx] = curr_val;
			curr_idx = next_idx;
			curr_val = next_val;
			v_p[last_idx] = INT_MIN; //visited
		}
		while(v_p[i]==INT_MIN)
			i++;
	}

	return;
}

vector<int> ApplyPermutationWrapper(vector<int> perm, vector<int> A) {
	ApplyPermutation2(&perm, &A);
  return A;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"perm", "A"};
  generic_test_main(argc, argv, param_names, "apply_permutation.tsv",
                    &ApplyPermutationWrapper);
  return 0;
}
