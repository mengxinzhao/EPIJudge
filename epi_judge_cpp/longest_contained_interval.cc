#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
using std::vector;
using std::max;
using std::unordered_map;
using std::sort;

// sort the vector
// the problem reduced to find the longest consective subarray -remove duplicated
// O(nlogn) running time
int LongestContainedRange(vector<int>& A) {

    sort(A.begin(), A.end());
    int start = 0;
    int max_length = INT_MIN;
    int i=0;
    int dup=0;
    while(i<A.size()-1) {
        if (A[i+1] - A[i] > 1) {
            max_length = max(max_length, i-start+1 - dup);
            start = i+1;
            dup = 0;
        }else if (A[i+1]== A[i])
            dup++;
        i++;
    }
    // the last one
    max_length = max(max_length, i-start+1-dup);
    return max_length;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "longest_contained_interval.tsv",
                    &LongestContainedRange);
  return 0;
}
