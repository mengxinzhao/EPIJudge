#include <vector>
#include <cstddef>
#include <algorithm>
#include <utility>
#include <iostream>
#include <climits>
using std::vector;
using std::max;
using std::min;

// extend the array and then apply standard max subarray sum algorithm
//O(N^2)
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

//final_max_subarray_sum = max(max_subarray_sum, total_sum - min_subarray_sum)
//min_subarray_sum [i] = min(min_subarray_sum[i-1],min_subarray_sum [i-1]+ A[i],A[i]
// O(n) run time
int MaxSubarraySumInCircular2(const vector<int>A) {
    int total_sum =A[0];
    int min_so_far, min_at_i;
    int max_so_far, max_at_i;
    
    max_so_far = max_at_i  = A[0];
    min_so_far = min_at_i  = A[0];
    
    for (size_t i=1;i<A.size();i++) {
        total_sum += A[i];
        max_at_i = max (max_at_i+A[i],A[i]);
        max_so_far = max(max_so_far, max_at_i);
        
        min_at_i = min (min_at_i + A[i],A[i]);
        min_so_far = min(min_at_i, min_so_far);
    }
    //std::cout<<"total_sum: "<< total_sum << std::endl;
    return max(total_sum - min_so_far, max_so_far);
}


#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names,
                    "maximum_subarray_in_circular_array.tsv",
                    &MaxSubarraySumInCircular2);
  return 0;
}
