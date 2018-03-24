#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <iostream>
using std::vector;
using std::priority_queue;
using std::min;
using std::tuple;
using std::min_element;
// merge sort the arrays
// keep the max_heap size =3 that tracks the minimum distance
// when all elements are visited
// the last popped element in the max_heap is the minimum distance

// O(Nlog(3)) complexity ~= O(N)
// N: total length of the merged array
// log(3) to insert an element into max_heap

struct Record {
    int distance;
    tuple<int,int,int>loc;
    Record(int _distance,tuple<int,int,int>_loc) : distance(_distance),loc(_loc) {}
};

struct Compare {
    bool operator() (const Record &lhs, const Record &rhs) const {
        return lhs.distance < rhs.distance;
    }
};

bool get_next_min(const vector<vector<int>>& sorted_arrays, vector<int> &Idx, int &next_min){
    vector<int> tmp;
    bool min_exist = false;
    int min_idx = 0, max_idx = 0;
    int min = INT_MAX,max = INT_MIN;
    for (int i = 0; i< sorted_arrays.size();i++) {
        if ( Idx[i] < sorted_arrays[i].size () )
            tmp.push_back(sorted_arrays[i][Idx[i]]);
        else
            tmp.push_back(sorted_arrays[i][sorted_arrays[i].size()-1]);
        if (Idx[i] < sorted_arrays[i].size () && min > sorted_arrays[i][Idx[i]]) {
            min_exist = true;
            min =sorted_arrays[i][Idx[i]];
            min_idx = i;
        }
    }
    if (min_exist) {
        std::sort(tmp.begin(),tmp.end());
        next_min = *std::prev(tmp.end()) - *tmp.begin();
//        std::cout<<"min: "<<sorted_arrays[min_idx][Idx[min_idx]] <<std::endl;
//        std::cout<<"next_min: "<<next_min<<std::endl;
        Idx[min_idx]++;
        return true;
    }
    else
        return false;

}

int FindClosestElementsInSortedArrays(
    const vector<vector<int>>& sorted_arrays) {
    //max_heap
    priority_queue<int, vector<int>, std::less<int>> tbl;
    vector<int> Idx(sorted_arrays.size(),0);
    int heap_size = sorted_arrays.size();
    int min = INT_MAX;
    while (get_next_min(sorted_arrays,Idx,min)) {
        tbl.emplace(min);
        if (tbl.size() > heap_size)
            tbl.pop();
    }
    
    while(tbl.size()>1)
        tbl.pop();
    return tbl.top();
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"sorted_arrays"};
  generic_test_main(argc, argv, param_names,
                    "minimum_distance_3_sorted_arrays.tsv",
                    &FindClosestElementsInSortedArrays);
  return 0;
}
