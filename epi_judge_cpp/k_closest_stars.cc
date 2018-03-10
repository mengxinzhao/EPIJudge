#include <algorithm>
#include <cmath>
#include <vector>
#include <iterator>
#include <queue>

#include "test_framework/test_utils.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;

struct Star {
  bool operator < (const Star& that) const {
    return Distance() < that.Distance();
  }

  double Distance() const { return sqrt(x * x + y * y + z * z); }

  double x, y, z;
};

template <typename T>
class Compare
{
public:
    // similar to std::greater
    bool operator() (T one, T two) {
        return (one < two);
    }
};
// Build a max heap with k elements
// keep poping the top and inserting new element will all data is processed and return the left k max in the heap
// O(log(k))  insertion complexity
// O(Nlog(k)) total complexity
vector<Star> FindClosestKStars(vector<Star>::const_iterator stars_begin,
                               const vector<Star>::const_iterator& stars_end,
                               int k) {
    std::priority_queue<Star, vector<Star>, Compare<Star> > max_heap;
    vector<Star> result;

    auto it = stars_begin;
    while(it != stars_end) {
        max_heap.emplace(*it);
        it++;
        // only keep k elements in the heap
        if (max_heap.size()>k)
            max_heap.pop();
    }

    while(!max_heap.empty()) {
        result.push_back(max_heap.top());
        max_heap.pop();
    }
    // reverse the array to become  distance ascending order
    std::reverse(result.begin(), result.end());
    return result;
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
  std::vector<std::string> param_names{"stars", "k"};
  generic_test_main(argc, argv, param_names, "k_closest_stars.tsv",
                    &FindClosestKStarsWrapper, &Comp);
  return 0;
}
