#include <vector>

#include "test_framework/test_timer.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::sort;


struct Interval {
    struct Endpoint {
        bool is_closed;
        int val;
        Endpoint(bool _closed,int _val):is_closed(_closed),val(_val) {}
        Endpoint() {
            is_closed = false;
            val =0;
        }
        bool operator<(const Endpoint &lh) const {
            return (val < lh.val);
        }
        bool operator<=(const Endpoint &lh) const {
            return (val <= lh.val);
        }
        bool operator==(const Endpoint &lh) const {
            return (val == lh.val) && (is_closed == lh.is_closed);
        }
    };
    Endpoint left, right;
    Interval(Endpoint _left, Endpoint _right): left(_left),right(_right){}
};

vector<Interval> UnionOfIntervals(vector<Interval> intervals) {
    vector<Interval:: Endpoint> left_points;
    vector<Interval:: Endpoint> right_points;
    vector<Interval> result;
    for (int i=0; i< intervals.size();i++) {
        left_points.push_back(intervals[i].left);
        right_points.push_back(intervals[i].right);
    }

    sort(left_points.begin(),left_points.end());
    sort(right_points.begin(),right_points.end());

    Interval::Endpoint left(false,0),right(false,0);
    int left_idx= 0, right_idx= 0;
    int overlaps = 0;

    while(left_idx < left_points.size() || right_idx  < right_points.size()) {
        if (left_idx < left_points.size() && left_points[left_idx]<=right_points[right_idx] ) {
            if (overlaps ==0) {
                left = left_points[left_idx];
                overlaps++;
            }else if (left.is_closed == false && left_points[left_idx].is_closed == true)
                left.is_closed = true;
            left_idx++;
        } else {
            if (overlaps - 1 ==0) {
                right = right_points[right_idx];
                result.emplace_back(left,right);
                overlaps--;
            }else if (overlaps==0 && right.is_closed == false && right_points[right_idx].is_closed == true) {
                result[result.size()-1].right.is_closed = true;
            }
            right_idx++;
        }
    }
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
