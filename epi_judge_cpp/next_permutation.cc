#include <vector>
#include <algorithm>

using std::vector;

vector<int> NextPermutation(vector<int> perm) {
	// Implement this placeholder.
    int size = perm.size();

	int i=0, pos = 0;
	// the longest decreasing pos <2,5,4,3,1,0> pos = 1
	for (i=size-1; i >0;i--)
		if (perm[i] >perm[i-1]) {
			pos = i;
			break;
		}
	//all in order no permutation
	if (i <=0)
		return {};
	//search for the 1st element from the end to the pos that
	// is bigger than perm[pos-1] swap_pos =3
	int swap_pos = 0;
	for (int i=size-1; i >=pos;i--)
		if (perm[i] > perm[pos-1]) {
			swap_pos = i;
			break;
		}
	std::swap(perm[pos-1],perm[swap_pos]);  //<3,5,4,2,1,0>
	//reverse the array from the end to the pos  // <3,0,1,2,4,5>
	for (int i = 0; i< (size -pos)/2;i++){
		std::swap(perm[i+pos],perm[size-i-1]);
	}

    return perm;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "next_permutation.tsv", &NextPermutation);
  return 0;
}
