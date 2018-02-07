#include <algorithm>
#include <cmath>
#include <vector>

#include "test_framework/test_utils.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;

struct Star {
  bool operator<(const Star& that) const {
    return Distance() < that.Distance();
  }

  double Distance() const { return sqrt(x * x + y * y + z * z); }

  double x, y, z;
};

vector<Star> FindClosestKStars(vector<Star>::const_iterator star_begin,
                               const vector<Star>::const_iterator& star_end,
                               int k) {
  // Implement this placeholder.
  return {};
}

template <>
struct SerializationTraits<Star> : UserSerTraits<Star, double, double, double> {
};

std::ostream& operator<<(std::ostream& out, const Star& s) {
  return out << s.Distance();
}

bool Comp(const vector<double>& expected, vector<Star> output) {
  if (output.size() != expected.size()) {
    return false;
  }

  std::sort(begin(output), end(output));

  for (int i = 0; i < output.size(); ++i) {
    if (!DefaultComparator()(output[i].Distance(), expected[i])) {
      return false;
    }
  }
  return true;
}

vector<Star> FindClosestKStarsWrapper(const vector<Star>& stars, int k) {
  return FindClosestKStars(cbegin(stars), cend(stars), k);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "k_closest_stars.tsv",
                    &FindClosestKStarsWrapper, &Comp);
  return 0;
}
