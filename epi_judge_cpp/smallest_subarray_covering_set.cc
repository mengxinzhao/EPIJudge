#include <string>
#include <unordered_set>
#include <vector>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::string;
using std::unordered_set;
using std::vector;

struct Subarray {
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords) {
  // Implement this placeholder.
  return {0, 0};
}

int FindSmallestSubarrayCoveringSetWrapper(TestTimer &timer,
                                           const vector<string> &v,
                                           const unordered_set<string> &s) {
  auto copy = s;

  timer.Start();
  auto result = FindSmallestSubarrayCoveringSet(v, s);
  timer.Stop();

  if (result.start < 0 || result.start >= v.size() || result.end < 0 ||
      result.end >= v.size() || result.start > result.end) {
    throw TestFailureException("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++) {
    copy.erase(v[i]);
  }

  if (!copy.empty()) {
    throw TestFailureException("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char *argv[]) {
  generic_test_main(argc, argv, "smallest_subarray_covering_set.tsv",
                    &FindSmallestSubarrayCoveringSetWrapper);
  return 0;
}
