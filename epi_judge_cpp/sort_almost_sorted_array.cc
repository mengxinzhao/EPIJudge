#include <vector>
#include <queue>
#include <iterator>

using std::vector;
// Build a min heap with k elements
// keep poping the top and inserting new element will iterating to the end of the sequence
// O(log(k))  insertion complexity
// O(Nlog(k)) total complexity
vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end, int k) {
    
    std::priority_queue<int, vector<int>,std::greater<int>> min_heap;
    vector<int> result;
    // build min heap first
    for (auto it = sequence_begin; it != sequence_begin + k; it++) {
        min_heap.emplace(*it);
    }
    auto it = sequence_begin + k;
    while(it != sequence_end) {
        result.push_back(min_heap.top());
        min_heap.pop();
        min_heap.emplace(*it);
        it++;
    }
    while(!min_heap.empty()) {
        result.push_back(min_heap.top());
        min_heap.pop();
    }
    return result;
}

vector<int> SortApproximatelySortedDataWrapper(const vector<int>& sequence,int k) {
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"sequence", "k"};
  generic_test_main(argc, argv, param_names, "sort_almost_sorted_array.tsv",
                    &SortApproximatelySortedDataWrapper);
  return 0;
}
