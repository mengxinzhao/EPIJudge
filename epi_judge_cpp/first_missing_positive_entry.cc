#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;

// A is passed by value argument, since we change it.
int FindFirstMissingPositive(vector<int> A) {
	// 1st pass separate negative 0 and positive
	int pos = 0;
	for (int i =0; i < A.size(); i++) {
		if (A[i] <=0) {
			std::swap(A[i],A[pos++]);
		}
	}
	//std::cout<<"pos: "<<pos<<std::endl;

	// positive numbers are after pos
	// adjust array such that A[i] = A[A[i]+1-pos]
	for (int i = pos;i < A.size();i++) {
        while ((A[i] -1 +pos ) < A.size() &&A[i] -1 +pos>=0 &&  A[i]!=A[A[i] -1 +pos]) {
			std::swap(A[i],A[A[i]-1+pos]);
		}
	}
	// the first element A[i]!=i+1-pos shows that it misses i+1-pos
    if (pos < A.size()) {
        for (int i=pos; i< A.size();i++)
            if (A[i] != i+1-pos)
                return i+1-pos;
        
        return A.size()+1-pos;
    } else
        return 1;

}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "first_missing_positive_entry.tsv",
                    &FindFirstMissingPositive);
  return 0;
}
