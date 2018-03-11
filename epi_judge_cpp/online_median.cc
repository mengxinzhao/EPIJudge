#include <vector>
#include <iterator>
#include <queue>

using std::vector;

// build a min and max heap. min heap keeps the bigger half and max heap keeps the smaller half
// 1st element inserted to min heap
// media = 1/2 (min_heap.top() + max_heap.top())
// O(log(n)) insertion complexity
vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator& sequence_end) {
    std::priority_queue<double, vector<double>,std::greater<double> > min_heap;
    std::priority_queue<double,vector<double>, std::less<double>>max_heap;
    vector<double> result;
    // the first one
    min_heap.emplace(*sequence_begin);
    result.push_back(min_heap.top());
    
    auto it = sequence_begin+1;
    while(it!= sequence_end) {
        if ( *it > min_heap.top()) {
            min_heap.emplace(*it);
        }else {
            max_heap.emplace(*it);
        }
        // if the size of the two is not balanced move the top from max_heap to min_heap
        // or the other direction
        if (max_heap.size() > min_heap.size()+1) {
            min_heap.emplace(max_heap.top());
            max_heap.pop();
        }else if  (min_heap.size() > max_heap.size()+1) {
            max_heap.emplace(min_heap.top());
            min_heap.pop();
        }
        // median value
        if (max_heap.size() == min_heap.size())
            result.push_back(0.5*(max_heap.top()+ min_heap.top()));
        else {
            if (max_heap.size() > min_heap.size())
                result.push_back(max_heap.top());
            else
                result.push_back(min_heap.top());
        }
        it++;

    }
    return result;
}

vector<double> OnlineMedianWrapper(const vector<int>& sequence) {
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"sequence"};
  generic_test_main(argc, argv, param_names, "online_median.tsv",
                    &OnlineMedianWrapper);
  return 0;
}
