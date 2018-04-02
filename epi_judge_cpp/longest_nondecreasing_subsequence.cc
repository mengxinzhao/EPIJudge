#include <vector>
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <utility>
using std::vector;
using std::max;
using std::min;
using std::pair;
// LSN[i] = max(sequence from (i+1...N), sequence from (k ...N))  k is the first element A[k] > A[i]
//  when A[i] > A[i-1] in LSN[i+1]
// else LSN[i] =  LSN[i+1]+1 when A[i] <= A[i-1]
int LongestNondecreasingSubsequenceLength(const vector<int>& A) {
    vector<pair<int,int>> LSN(A.size(),pair<int,int>(0,0));
    LSN[A.size()-1] = {A[A.size()-1],1};
    int curr_min = A[A.size()-1];
    for (int i = A.size()-2;i>=0;i--) {
        //std::cout<<"curr_min: " << curr_min<<" ";
        if (A[i] >curr_min) {
            //
            int num=0;
            int j=i+1;
            int max_after_i = 0;
            for (; j<A.size();j++){
                if (A[j]>=A[i] && A[j]<=LSN[j].first) {
                   max_after_i = max(max_after_i,LSN[j].second +1);
                }
            }
            if (LSN[i+1].second > max_after_i) {
                LSN[i]= LSN[i+1];
            }
            else {
                LSN[i]= {A[i], max_after_i};
                curr_min = A[i];
            }
         }
        else {
            LSN[i].second = LSN[i+1].second + 1;
            LSN[i].first = A[i];
            curr_min = A[i];
        }
        //std::cout<<"i:" << i << " LSN: " <<LSN[i].first<<", "<<  LSN[i].second << std::endl;
    }
    return LSN[0].second;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names,
                    "longest_nondecreasing_subsequence.tsv",
                    &LongestNondecreasingSubsequenceLength);
  return 0;
}
