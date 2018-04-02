#include <vector>
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <utility>
#include <climits>
using std::vector;
using std::max;
using std::min;
using std::pair;


// LSN[i] longest nodecreasing subsequence ending in i-th element
// LSN[i] = 1 + max(LSN[j]) j=0,...i-1 if (A[i]>=A[j])
// because LSN[i] might be 1 if A[i] is small than all of its previous
// solution needs to do a linear seach
// solution =  max(LSN[i])
// O(N^2) complexity
int LongestNondecreasingSubsequenceLength2(const vector<int>& A) {
    vector<int> LSN(A.size(), 1);
    for (int i=1; i<A.size();i++) {
        int max_at_i = INT_MIN;
        for (int j=0; j<=i-1; j++) {
            if (A[i] >= A[j]) {
                if (LSN[j] >=max_at_i)
                    max_at_i = LSN[j];
            }
        }
        if (max_at_i >INT_MIN)
            LSN[i] = max_at_i + 1;

    }
    int max_at_i = INT_MIN;
    for (int i=0; i<A.size();i++) {
        if (LSN[i] >=max_at_i)
            max_at_i = LSN[i];
    }
        
    return max_at_i;
    
}
#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names,
                    "longest_nondecreasing_subsequence.tsv",
                    &LongestNondecreasingSubsequenceLength2);
  return 0;
}
