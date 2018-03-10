#include <vector>
#include <utility>
#include <cstddef>
#include <algorithm>
#include <queue>
#include <limits.h>
#include <iostream>

using std::vector;

// decomposite array into 2K monotonically increasing array
// use helper array to record decomposited array start and end index
// build a min heap on first 2K element and keep poping up the min element and inserting new element that is
// the smallest one from 2K arrays.
// keeping doing it till all elements are popped.

// O(n) scan
vector<std::pair<int,int>> decomposite(vector<int> &A) {
    // return an index array that tracks where each decomposite subarray start and end
    vector<std::pair<int,int>> idx;
    bool increasing = true;
    int start=0;
    size_t i =0;
    for (; i < A.size()-1;i++) {
        if (increasing) {
            if (A[i] > A[i+1] ) {
                increasing = false;
                idx.emplace_back(std::make_pair(start, i));
                // not do anything. update the start for the next sequence
                start = i+1;
            }
        }else {
            if (A[i] < A[i+1]) {
                idx.emplace_back( std::make_pair(start, i));
                // reverse (start, end)
                for (size_t j = 0; j <= (i-start)/2; j++) {
                    std::swap(A[j+ start], A[i-j]);
                }
                // update the start for the next sequence
                start = i+1;
                increasing = true;
            }
        }
    }

    idx.emplace_back( std::make_pair(start, i));
    //the last sequence is a decreasing one. needs to be reverted
    if (!increasing) {
        for (size_t j = 0; j <= (i-start)/2; j++) {
            std::swap(A[j+ start], A[i-j]);
        }
    }
    
    
    return idx;

}

// O(k) compare
std::pair<int,int *>  get_smallest(const vector<int> &A, vector<std::pair<int,int>> &idx) {
    std::pair<int,int *> min_v = std::make_pair(INT_MAX,nullptr);// min value, where it is in the index array
    for (size_t i=0; i < idx.size(); i++) {
        if ((idx[i].first <= idx[i].second) && (min_v.first  >= A[idx[i].first])) {
            min_v.first = A[idx[i].first];
            min_v.second = &idx[i].first;
        }
    }
    if (min_v.second != nullptr) {
        (*min_v.second)++;
    }
    return min_v;
    
}

// O(Nlog(k))
vector<int> merge_array(const vector<int> &A, vector<std::pair<int,int>> &idx) {
    std::priority_queue<int,vector<int>,std::greater<int>> min_heap;
    vector<int> result;
    
    //build the min heap
    for (size_t i=0; i < idx.size(); i++) {
        min_heap.emplace(A[idx[i].first]);
        idx[i].first++;
    }
    while(!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
        //
        auto ele = get_smallest(A,idx);
        if (ele.second!=nullptr) {
            min_heap.emplace(ele.first);
        }
    }
    
    return result;
}

vector<int> SortKIncreasingDecreasingArray(vector<int>& A) {
  // Implement this placeholder.
    vector<std::pair<int,int>> decomposite_idx = decomposite(A);
    return merge_array(A,decomposite_idx);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names,
                    "sort_increasing_decreasing_array.tsv",
                    &SortKIncreasingDecreasingArray);
  return 0;
}
