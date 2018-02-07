  #include <vector>

using std::vector;

// Returns the number of valid entries after deletion.
int DeleteDuplicates(vector<int>* A_ptr) {
  // Implement this placeholder.
    vector<int> & v = *A_ptr;

	if (v.empty())
		return 0;

    if (v.size() == 1)
      return 1;

	int pos = 0;
	for (int i=0; i < v.size()-1;i++) {
		if (v[i]!= v[i+1])
			v[pos++] = v[i];
	}
	v[pos++] = v[v.size()-1];

    return pos;
}

vector<int> DeleteDuplicatesWrapper(vector<int> A) {
  int end = DeleteDuplicates(&A);
  A.resize(end);
  return A;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "sorted_array_remove_dups.tsv",
                    &DeleteDuplicatesWrapper);
  return 0;
}
