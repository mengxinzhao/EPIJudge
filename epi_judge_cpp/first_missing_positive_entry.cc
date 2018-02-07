#include <vector>
#include <iostream>
#include <algorithm>

using std::vector;

// A is passed by value argument, since we change it.
int FindFirstMissingPositive(vector<int> A) {
	// Implement this placeholder.
	vector<int> &v = A;
	// 1st pass separate negative 0 and positive
	int pos = 0;
	for (int i =0; i < v.size()-1; i++) {
		if (v[i] <=0) {
			std::swap(v[i],v[pos++]);
		}
	}
	std::cout<<"pos: "<<pos<<std::endl;

	// positive numbers are after pos
	// adjust array such as A[i] = i+1-pos
	for (int i = pos;i < v.size();i++) {
		while (v[i] -1 +pos  < v.size() && v[i]!=v[v[i] -1 +pos]) {
			std::swap(v[i],v[v[i]-1+pos]);
		}
	}
	// the first element A[i]!=i+1-pos shows that it misses i+1-pos
	for (int i=pos; i< v.size();i++)
		if (v[i]!= i+1-pos)
			return i+1-pos;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "first_missing_positive_entry.tsv",
                    &FindFirstMissingPositive);
  return 0;
}
