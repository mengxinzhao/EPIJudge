#include <vector>
#include <iostream>
#include <cstddef>
using std::vector;

// merge sort and count inversion when merging
// return index array instead of  value array
// O(NLog(N))
vector<int> countInversionsHelper(vector<int> &A, int &inversion_count, int left, int right) {
	if (left == right)
		return vector<int>(1,left);

	size_t mid = (left + right)/2;

    vector<int> partition_left = countInversionsHelper(A, inversion_count,left, mid);
    vector<int> partition_right =countInversionsHelper(A,inversion_count,mid+1, right);
    // merge and count inversion
    vector<int> merged(partition_left.size()+partition_right.size(),0);
    size_t i = 0, j=0,k=0;

    while(i < partition_left.size() && j< partition_right.size()) {
        if (A[partition_left[i]] <= A[partition_right[j]] ) {
            merged[k++] = partition_left[i++];
        }else {
             if (partition_left[i] < partition_right[j])
                 // from i to mid in the left part,  all biggher than A[partition_right[j]]. all inversion
                 inversion_count += partition_left.size() - i ;
             merged[k++] = partition_right[j++];

        }
    }
    
    if(i < partition_left.size() && j== partition_right.size()) {
        while (i < partition_left.size()) {
            merged[k++] = partition_left[i++];
        }
    }
    if(j< partition_right.size() && i == partition_left.size() ){
        while (j < partition_right.size()) {
            merged[k++] = partition_right[j++];
        }
    }
    return merged;
}



int CountInversions(vector<int> A) {
  // Implement this placeholder.

    int num_inversion = 0;
	vector<int> merged = countInversionsHelper(A, num_inversion, 0,A.size()-1);
//    for (const auto &e : merged)
//        std::cout<<A[e]<<" ";
//    std::cout<<std::endl;
    return num_inversion;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "count_inversions.tsv",
                    &CountInversions);
  return 0;
}
