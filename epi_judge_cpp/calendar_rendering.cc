#include <vector>
#include <algorithm>
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::sort;


struct Event {
  int start, finish;
};

// sort the event based on start and end time seperately and put into 2 arrays
// merge the sorted array
// iterate through the final array
// O(nlog(n)) sort 2 array  n= A.size
// O(n) merge
int FindMaxSimultaneousEvents(const vector<Event>& A) {
    // ascending order in finish time
    vector<int> start(A.size(),0);
    vector<int> finish(A.size(),0);
    for (int i=0;i<A.size();i++) {
        start[i] = A[i].start;
        finish[i] = A[i].finish;
    }
    sort(start.begin(),start.end());
    sort(finish.begin(),finish.end());
    int start_idx=0, leave_idx = 0;
    int overlaps = 0,max_overlaps = -1;
    // iterate through event.
    // once start is iterated overlap number can only go down
    while(start_idx < A.size()) {
        // when start and finish happen to be the same count start first
        // and then leave. Otherwise won't pass the judge
        if (start[start_idx] <=finish[leave_idx]){
            overlaps++;
            start_idx++;
            if (overlaps > max_overlaps)
                max_overlaps = overlaps;
        }else {
            overlaps--;
            leave_idx++;
        }
    }
    
    
    
  return max_overlaps;
}

template <>
struct SerializationTraits<Event> : UserSerTraits<Event, int, int> {};

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "calendar_rendering.tsv",
                    &FindMaxSimultaneousEvents);
  return 0;
}
