#include <vector>
#include <queue>
#include <climits>
#include <iostream>
using std::vector;
using std::priority_queue;

//linear merge sort takes O(nm) m arrays,n array length for each array
//min_heap size m O(m) build
//use additinal m space to track what the next available input to be O(m)
//heap insert m element O(log(m))
// total O(N(logm + O(m))) ~ O(Nlogm)
bool get_next(const vector<vector<int>>& sorted_arrays, vector<int> &next_avail_idx,int &next_min) {
    bool min_exist = false;
    int min = INT_MAX;
    int array_idx = 0;
    for (int i = 0; i< sorted_arrays.size();i++) {
        if ( next_avail_idx[i] < sorted_arrays[i].size () && min > sorted_arrays[i][next_avail_idx[i]] ) {
            min_exist = true;
            min =sorted_arrays[i][next_avail_idx[i]];
            array_idx = i;
        }
    }
    if (min_exist) {
        next_avail_idx[array_idx]++;
        next_min = min;
    }
    return min_exist;
}
vector<int> MergeSortedArrays(const vector<vector<int>>& sorted_arrays) {
    vector<int> next_idx(sorted_arrays.size(),1);
    priority_queue<int,vector<int>,std::greater<int>> min_heap;
    vector<int> result;
    // build a m size min_heap
    for(int i=0; i< sorted_arrays.size();i++){
        min_heap.push(sorted_arrays[i][0]);
    }
    while(!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
        // insert a new element
        int min = INT_MAX;
        if (get_next(sorted_arrays,next_idx,min)) {
            //std::cout<<min<<std::endl;
            min_heap.push(min);
        }
    }
    
    return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"sorted_arrays"};
  generic_test_main(argc, argv, param_names, "sorted_arrays_merge.tsv",
                    &MergeSortedArrays);
  return 0;
}
