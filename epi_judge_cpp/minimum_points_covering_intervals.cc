#include <vector>

#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::sort;
using std::min;
using std::max;

struct Interval {
    int left, right;
    bool operator < (const Interval &lh) const {
        return right < lh.right;
    }
};

// this is finding the and set of intervals.
// sort the right point
// merge = (max(left, new_left), min(right, new_right))
int FindMinimumVisits(vector<Interval> intervals) {

    Interval merged;
    int min_point = 0;
    
    if (intervals.size () == 0)
        return 0;
    
    sort(intervals.begin(),intervals.end());
    merged = intervals[intervals.size()-1];
    for (int i = intervals.size()-2; i>=0;i--) {
        if (intervals[i].right >= merged.left) {
            merged={ max(merged.left, intervals[i].left), min(merged.right, intervals[i].right) };
        }else {
            min_point++;
            // the point is merged.right
            merged = intervals[i];
        }
    }
    // the last one
    min_point++;
    return min_point;
}

template <>
struct SerializationTraits<Interval> : UserSerTraits<Interval, int, int> {};

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"intervals"};
  generic_test_main(argc, argv, param_names, "points_covering_intervals.tsv",
                    &FindMinimumVisits);
  return 0;
}
