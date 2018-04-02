#include <vector>
#include <cstddef>
#include <algorithm>
#include <utility>
#include <iostream>
#include <climits>
using std::vector;
using std::max;


// extend the array and then apply standard max subarray sum algorithm
int MaxSubarraySumInCircular(const vector<int>& A) {
    vector<int>B(A);
    B.insert(B.end(),A.begin(),A.end());
    int max_so_far,max_i;
    vector<int>M(A.size(),0);
    for (int i=0; i<A.size();i++) {
        max_so_far = max_i= B[i];
        for(int j=i+1;j<i+A.size();j++) {
            max_i = max(B[j],max_i + B[j]);
            max_so_far = max(max_so_far, max_i);
        }
        M[i] = max_so_far > M[i]? max_so_far : M[i];
    }
    int max_sum = INT_MIN;
    for (int i=0;i<M.size();i++)
        if (M[i] > max_sum)
            max_sum = M[i];
    return max_sum;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names,
                    "maximum_subarray_in_circular_array.tsv",
                    &MaxSubarraySumInCircular);
  return 0;
}
