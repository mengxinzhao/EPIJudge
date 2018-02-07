#include <vector>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::vector;

int SearchEntryEqualToItsIndex(const vector<int>& A) {
  // Implement this placeholder.
	int left = 0, right = A.size()-1, mid;

	while(left <= right) {
		mid = (left + right )/2;// assuming no overflow
		if (A[mid] > mid) {
			// A is sorted so  A[mid] < A[A[mid]]
			//                 mid  <  A[mid]
			// to find A[mid] = mid needs to move
			right = mid-1;
		}else if (A[mid] == mid)
			return mid;
		else {
			// A is sorted so  A[A[mid]] <    A[mid]
			//                 A[mid]    <    mid
			// to find A[mid] = mid needs to move
			left = mid+1;
		}
	}
  return -1;
}

void SearchEntryEqualToItsIndexWrapper(TestTimer& timer, const vector<int>& A) {
  timer.Start();
  int result = SearchEntryEqualToItsIndex(A);
  timer.Stop();
  if (result != -1) {
    if (A[result] != result) {
      throw TestFailureException("Entry does not equal to its index");
    }
  } else {
    for (int i = 0; i < A.size(); ++i) {
      if (A[i] == i) {
        throw TestFailureException(
            "There are entries which equal to its index");
      }
    }
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "A"};
  generic_test_main(argc, argv, param_names, "binary_search_ai=i.tsv",
                    &SearchEntryEqualToItsIndexWrapper);
  return 0;
}
