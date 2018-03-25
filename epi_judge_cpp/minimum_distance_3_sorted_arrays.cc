#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
using std::vector;
using std::priority_queue;
using std::min;
using std::tuple;
using std::min_element;
using std::multimap;
using std::numeric_limits;
using std::set;

// set keeps unique element sorted.
// when two values are the same need to choose the one
// from the smaller idx array
struct Record {
    Record(int _array_idx, int _curr_idx, int _end_idx,int _val):array_idx(_array_idx),curr_idx(_curr_idx),end_idx(_end_idx), val(_val) {}
    bool operator < (const Record &lh) const {
        return (val< lh.val || ((val == lh.val) && (array_idx < lh.array_idx)));
    }
    int array_idx;
    int curr_idx;
    int end_idx;
    int val;
};

// merge sort the arrays by each time picking up the minium element from
// A,B,C of current idx
// the min distance comes from the smallest max distance of a triplet visited

// O(Nlog(k)) complexity ~= O(N)
// N: total length of the merged array, k = 3 . set uses AVL tree the sorting O(klog(k))

int FindClosestElementsInSortedArrays(
    const vector<vector<int>>& sorted_arrays) {
    //use set to track. It is sorted by val
    set<Record> current;
    int min_distance = INT_MAX;
    int max_distance  = INT_MIN;
    
    //initial current track
    for (int i=0;i<sorted_arrays.size();i++) {
        current.emplace(i, 0,sorted_arrays[i].size(),sorted_arrays[i][0]);
    }
    while (true) {
        max_distance = std::prev(current.end())->val -  current.begin()->val ;
        min_distance = min(min_distance, max_distance);
        //discard the minimum val element
        int array_idx = current.begin()->array_idx;
        int next_idx = current.begin()->curr_idx;
        int end_idx = current.begin()->end_idx;
        next_idx++;
        // when one array runs to the end exit
        // if <i,j,k> is the min_distance identitified before j runs to the end(say j is B's idx)
        // the triplet distance found after B.size()-1 can't be less than <i,j,k>
        // because distance = max(distance_AB, distance_AC, distance_BC)
        // now distance_AB, distance_BC will be no less than distance_A[i]B[j], distance_B[j]C[k]
        if (next_idx >= end_idx){
            //std::cout<<"min_distance: "<<min_distance<<std::endl;
            return min_distance;
        }
        current.erase(current.begin());
        current.emplace(array_idx,next_idx,end_idx,sorted_arrays[array_idx][next_idx]);
    }

    return min_distance;
}


#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"sorted_arrays"};
  generic_test_main(argc, argv, param_names,
                    "minimum_distance_3_sorted_arrays.tsv",
                    &FindClosestElementsInSortedArrays);
  return 0;
}
