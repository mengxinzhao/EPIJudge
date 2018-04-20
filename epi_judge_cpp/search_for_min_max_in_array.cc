#include <vector>
#include <algorithm>
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::min;
using std::max;
struct MinMax {
  int smallest, largest;
};

MinMax FindMinMax(const vector<int>& A) {
    if (A.size() == 1)
        return {A[0],A[0]};
    else if (A.size() == 2) {
        return {min(A[0],A[1]), max(A[0],A[1])};
    }
    MinMax val;
    int start;
    if (A.size()%2==0) {
        val = {min(A[0],A[1]), max(A[0],A[1])};
        start = 2;
    }
    else {
        val = {A[0],A[0]};
        start =1;
    }
    // 3* n/2 comparision
    for (int i =start ; i< A.size();i+=2) {
        int pair_min = min(A[i],A[i+1]);
        if (pair_min == A[i]) {
            val.largest = max(A[i+1],val.largest);
            val.smallest = min(A[i], val.smallest);
        }else {
            val.largest = max(A[i],val.largest);
            val.smallest = min(A[i+1], val.smallest);
        }
    }
    return val;
}


template <>
struct SerializationTraits<MinMax> : UserSerTraits<MinMax, int, int> {};

bool operator==(const MinMax& lhs, const MinMax& rhs) {
  return std::tie(lhs.smallest, lhs.largest) ==
         std::tie(rhs.smallest, rhs.largest);
}

std::ostream& operator<<(std::ostream& out, const MinMax& x) {
  return out << "min: " << x.smallest << ", max: " << x.largest;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "search_for_min_max_in_array.tsv",
                    &FindMinMax);
  return 0;
}
