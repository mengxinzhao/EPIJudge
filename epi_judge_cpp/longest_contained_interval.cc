#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <climits>
#include <iterator>
#include <iostream>
#include <utility>
using std::vector;
using std::max;
using std::unordered_map;
using std::sort;
using std::distance;
using std::map;
using std::pair;
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

// union find. not efficient. need path compression 
#include <utility>
int LongestContainedRange_Unionfind(const vector<int> &A) {
    unordered_map<int, pair<int,bool> > cache;// map element to its index
    unordered_map<int, int> count_freq;   //map root element loc to the number of children under it
    
    for (size_t i= 0; i< A.size();i++) {
        if (cache.find(A[i]) == cache.end())
            cache[A[i]] = {i, false};
    }
    
    // union the element to its parent that satisfies the constraints
    // if A0...An is consecutive subarray and A[i] < A[i+1] < ...A[n], map A[i] to n
    // till there is no element can be merged
    for (auto iter= cache.begin(); iter!= cache.end();iter++) {
        //std::cout<<"checking... "<<iter->first << "@ " <<  iter->second.first<<std::endl;
        if (iter->second.first == distance(A.begin(),A.begin()+iter->second.first ) && iter->second.second == false)   {// equal to its original loc, otherwise this element has been merged-ed
            auto curr = iter;
            auto smaller_by_one = cache.find(curr->first-1);
            while(smaller_by_one!= cache.end()) {
                smaller_by_one->second.first = curr->second.first;
                smaller_by_one->second.second  = true;
                count_freq[curr->second.first]++;
                curr = smaller_by_one;
                smaller_by_one = cache.find(curr->first-1);
            }
        }
    }
    
    // return the cluster that has the most children.
    int max_count = INT_MIN;
    if (count_freq.size()>0) {
        for (auto &iter:count_freq){
            if (max_count < iter.second)
                max_count = iter.second;
        }
    }else
        max_count = 0;
    return max_count+1;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "longest_contained_interval.tsv",
                    &LongestContainedRange);
  return 0;
}
