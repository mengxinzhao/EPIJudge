#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <iostream>
#include <utility>

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

// union find.
// O(N) worst time  if all sequences have no gap and have to merge N-1 in the inner loop
int LongestContainedRange_Unionfind(const vector<int> &A) {
    unordered_map<int, int > cache;// map element to its index
    vector<int> rank(A.size(),1); // number of nodes under the root at index i
    vector<int> roots(A.size(),0); // track the ith node's parent point. initialize to itself
    // init
    for (size_t i= 0; i< A.size();i++) {
        cache[A[i]] = i;
        roots[i]=i;
        
    }
    int max_count = 1;
    // union the element to its parent that satisfies the constraints
    // if A0...An is consecutive subarray and A[i] < A[i+1] < ...A[n], map A[i] to n
    // till there is no element can be merged
    for (auto  elem : cache) {
        auto smaller_by_one = cache.find(elem.first-1);
        while(smaller_by_one!= cache.end()
              &&roots[smaller_by_one->second] == smaller_by_one->second) {
            // merge small cluster to a bigger cluster by changing
            // the parent pointer of the smaller cluster head
            roots[smaller_by_one->second] = elem.second;
            // parent's rank increase
            rank[elem.second] += rank[smaller_by_one->second];
            // find the next cluster
            int next = smaller_by_one->first-1;
            // delete the cache. now we only need to know its parent node
            cache.erase(smaller_by_one->first);
            smaller_by_one = cache.find(next);
        }
        auto bigger_by_one = cache.find(elem.first+1);
        while(bigger_by_one!= cache.end()
              &&roots[bigger_by_one->second] == bigger_by_one->second) {
            roots[bigger_by_one->second] = elem.second;
            rank[elem.second] += rank[bigger_by_one->second];
            int next = bigger_by_one->first+1;
            cache.erase(bigger_by_one->first);
            bigger_by_one = cache.find(next);
        }
        
        if (max_count < rank[elem.second])
            max_count = rank[elem.second];
    }
    
    // return the cluster that has the most children.
    return max_count;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "longest_contained_interval.tsv",
                    &LongestContainedRange_Unionfind);
  return 0;
}
