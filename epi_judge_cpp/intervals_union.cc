#include <vector>
#include <iostream>
#include "test_framework/test_timer.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::sort;
using std::min;
using std::max;


struct Interval {
    struct Endpoint {
        bool is_closed;
        int val;
        Endpoint(bool _closed,int _val):is_closed(_closed),val(_val) {}
        bool operator<(const Endpoint &lh) const {
            if (val < lh.val)
                return true;
            // [ < (
            else if (val == lh.val && is_closed == true && lh.is_closed != true)
                return true;
            else
                return false;
        }
        bool operator==(const Endpoint &lh) const {
            return (val == lh.val)&& (is_closed == lh.is_closed);
        }
        bool operator<=(const Endpoint &lh) const {
            return (val <= lh.val);
        }

    };
    Endpoint left, right;
    Interval(Endpoint _left, Endpoint _right): left(_left),right(_right){}
    bool operator<(const Interval &lh) const {
        return (left < lh.left) ;
    }
};

// O(Nlog(N)) complexity
vector<Interval> UnionOfIntervals(vector<Interval> intervals) {

    vector<Interval> result;
    sort(intervals.begin(), intervals.end());
    
    //merge one by one to a bigger interval
    Interval merged = intervals[0];
    for (int i=1; i< intervals.size();i++) {

        if (intervals[i].left.val < merged.right.val
            ||(intervals[i].left.val == merged.right.val
               && (intervals[i].left.is_closed| merged.right.is_closed))) {
            if ((merged.right.val < intervals[i].right.val )||
                ((merged.right.val ==intervals[i].right.val) && intervals[i].right.is_closed))
                merged.right =  intervals[i].right;
        }else {
            result.push_back(merged);
            merged = intervals[i];
        }
    }
    // the last merge
    result.push_back(merged);
    return result;
}

struct FlatInterval {
  int left_val;
  bool left_is_closed;
  int right_val;
  bool right_is_closed;

  FlatInterval(int left_val, bool left_is_closed, int right_val,
               bool right_is_closed)
      : left_val(left_val),
        left_is_closed(left_is_closed),
        right_val(right_val),
        right_is_closed(right_is_closed) {}

  explicit FlatInterval(Interval in)
      : left_val(in.left.val),
        left_is_closed(in.left.is_closed),
        right_val(in.right.val),
        right_is_closed(in.right.is_closed) {}

  operator Interval() const {
    return {{left_is_closed, left_val}, {right_is_closed, right_val}};
  }

  bool operator==(const FlatInterval& rhs) const {
    return std::tie(left_val, left_is_closed, right_val, right_is_closed) ==
           std::tie(rhs.left_val, rhs.left_is_closed, rhs.right_val,
                    rhs.right_is_closed);
  }
};

template <>
struct SerializationTraits<FlatInterval>
    : UserSerTraits<FlatInterval, int, bool, int, bool> {};

std::ostream& operator<<(std::ostream& out, const FlatInterval& i) {
  return out << (i.left_is_closed ? '<' : '(') << i.left_val << ", "
             << i.right_val << (i.right_is_closed ? '>' : ')');
}

std::vector<FlatInterval> UnionOfIntervalsWrapper(
    TestTimer& timer, const std::vector<FlatInterval>& intervals) {
  std::vector<Interval> casted;
  for (const FlatInterval& i : intervals) {
    casted.push_back(static_cast<Interval>(i));
  }

  timer.Start();
  std::vector<Interval> result = UnionOfIntervals(casted);
  timer.Stop();

  return {begin(result), end(result)};
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "intervals"};
  generic_test_main(argc, argv, param_names, "intervals_union.tsv",
                    &UnionOfIntervalsWrapper);
  return 0;
}
