#include <vector>

#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::min;
using std::max;

struct Interval {
  int left, right;
  Interval(int _left, int _right):left(_left),right(_right) {}
};

// O(NLogN) complexity
vector<Interval> AddInterval(const vector<Interval>& disjoint_intervals,
                             Interval new_interval) {
    vector<int> start (disjoint_intervals.size()+1,0);
    vector<int> finish(disjoint_intervals.size()+1,0);
    vector<Interval> result;
    int i=0;
    while (i<disjoint_intervals.size()) {
        start[i] = disjoint_intervals[i].left;
        finish[i] = disjoint_intervals[i].right;
        i++;
    }
    start[i] = new_interval.left;
    finish[i] =new_interval.right;
    
    // sort 2 array and merge sort
    sort(start.begin(),start.end());
    sort(finish.begin(),finish.end());
    int start_idx=0, finish_idx=0;
    int overlaps = 0;
    int left,right; // to track the new interval

    // when overlaps count reaches from 0--> local peak-->back to 0
    // that is a disjoint interval
    while (start_idx < start.size() || finish_idx < finish.size() ) {
        if (start_idx < start.size() && start[start_idx] <= finish[finish_idx]) {
            if (overlaps==0)
                left = start[start_idx];
            overlaps++;
            start_idx++;
        }else {
            if (overlaps-1==0)  {
                right = finish[finish_idx];
                result.emplace_back(left,right);
            }
            finish_idx++;
            overlaps--;
        }
    }

    return result;
}

// explore the fact that disjoint_intervals is already sorted.
// iterate through disjoint_intervals and only update the intervals that overlap with the
// newly added one
// O(n) runing time
vector<Interval> AddInterval2(const vector<Interval>& disjoint_intervals,
                             Interval new_interval) {
    vector<Interval> result;
    int i=0;

    while(i < disjoint_intervals.size()&& new_interval.left > disjoint_intervals[i].right) {
        result.emplace_back(disjoint_intervals[i]);
        i++;
    }
    
    // update the intervals. If there is overlap,the new one is [min(new_left, left), max(new_right, right)]
    while( i < disjoint_intervals.size() && new_interval.right >= disjoint_intervals[i].left) {
        new_interval = {min(new_interval.left, disjoint_intervals[i].left),
            max(new_interval.right, disjoint_intervals[i].right)};
        i++;
    }
    result.emplace_back(new_interval);
    
    // the rest from disjoint_intervals are untouched
    result.insert(result.end(), disjoint_intervals.begin()+i, disjoint_intervals.end());
    return result;
}



template <>
struct SerializationTraits<Interval> : UserSerTraits<Interval, int, int> {};

bool operator==(const Interval& a, const Interval& b) {
  return a.left == b.left && a.right == b.right;
}

std::ostream& operator<<(std::ostream& out, const Interval& i) {
  return EpiPrint(out, std::make_tuple(i.left, i.right));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"disjoint_intervals", "new_interval"};
  generic_test_main(argc, argv, param_names, "interval_add.tsv", &AddInterval2);
  return 0;
}
