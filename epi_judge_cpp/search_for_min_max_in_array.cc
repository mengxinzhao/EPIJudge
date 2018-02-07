#include <vector>

#include "test_framework/test_utils_serialization_traits.h"

using std::vector;

struct MinMax {
  int smallest, largest;
};

MinMax FindMinMax(const vector<int>& A) {
  // Implement this placeholder.
  MinMax val = {INT_MAX, INT_MIN};
  for (int i =0 ; i< A.size();i++) {
    if (val.smallest > A[i]) {
      val.smallest = A[i];
    }
    if (val.largest < A [i]) {
      val.largest = A[i];
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
  generic_test_main(argc, argv, "search_for_min_max_in_array.tsv", &FindMinMax);
  return 0;
}
