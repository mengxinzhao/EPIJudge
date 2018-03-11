#include <vector>
#include <queue>
#include <utility>
#include <iostream>

using std::vector;

//buid a max heap and iterate through A
//pop top =  A[i]
//push A[2*i+1], A[2*i+2] children into the heap
//repeat till k pops.
//complexity O(kLog(k))
template<typename T>
class Compare {
public:
    bool operator() (T one, T two) {
        return one.first < two.first;
    }
};
vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
    std::priority_queue<std::pair<int,int>,vector<std::pair<int,int>>, Compare<std::pair<int,int>>>max_heap;
    vector<int> result;
    max_heap.emplace(std::make_pair(A[0],0));
    
    while(result.size()<k) {
        auto top = max_heap.top();
        max_heap.pop();
        result.push_back(top.first);
        if ( 2*top.second+1 < A.size())
            max_heap.emplace(std::make_pair(A[2*top.second+1], 2*top.second+1));
        if ( 2*top.second+2 < A.size())
            max_heap.emplace(std::make_pair(A[2*top.second+2], 2*top.second+2));
    }
    
    return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A", "k"};
  generic_test_main(argc, argv, param_names, "k_largest_in_heap.tsv",
                    &KLargestInBinaryHeap,
                    &UnorderedComparator<std::vector<int>>);
  return 0;
}
