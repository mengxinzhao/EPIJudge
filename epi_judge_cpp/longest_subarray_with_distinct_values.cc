#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using std::vector;
using std::unordered_map;
using std::max;

//O(n) running time
int LongestSubarrayWithDistinctEntries(const vector<int>& A) {
    int start;
    int max_length = 0;
    unordered_map<int, int> cache; // cache element to its first appearing location afte start loc
    start = 0;
    int i=0;
    while (i< A.size()) {
        if (cache.find(A[i]) == cache.end()) {
            cache[A[i]]=i;
        }else {
            // has it cache
            if (cache[A[i]] >=start) {
                max_length = max((int)i-start,max_length);
                // reset the start
                // at this point we know that A[start] and A[i] is dup
                // things in between are good
                start= cache[A[i]]+1;
            }
            // update cache
            cache[A[i]]=i;
        }
        i++;
    }
  max_length = max(i-start,max_length);
  return max_length;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names,
                    "longest_subarray_with_distinct_values.tsv",
                    &LongestSubarrayWithDistinctEntries);
  return 0;
}
