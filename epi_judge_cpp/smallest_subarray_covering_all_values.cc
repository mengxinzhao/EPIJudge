#include <string>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::min;

struct Subarray {
  // Represent subarray by starting and ending indices, inclusive.
  int start, end;
};

struct Tracker {
    int start;
    int expect;
};

//O(N^2) running time
// not very efficient
Subarray FindSmallestSequentiallyCoveringSubset(
    const vector<string>& paragraph, const vector<string>& keywords) {
    int min_length = INT_MAX;
    int start;
    int end;
    for(int i=0;i < paragraph.size();i++) {
        if (paragraph[i] == keywords[0]) {
            Tracker tk = {.start = i, .expect = 1};// expecting next
            int j= i+1;
            while (j< paragraph.size()) {
                if (paragraph[j] == keywords[tk.expect]){
                    tk.expect++;
                }
                if (tk.expect == keywords.size() &&  j - tk.start < min_length) {
                    min_length = j-tk.start;
                    start = tk.start;
                    end = j;
                    break;
                }
                j++;
            }
        }
    }
    
  return {start, end};
}

int FindSmallestSequentiallyCoveringSubsetWrapper(
    TestTimer& timer, const vector<string>& paragraph,
    const vector<string>& keywords) {
  timer.Start();
  auto result = FindSmallestSequentiallyCoveringSubset(paragraph, keywords);
  timer.Stop();

  int kw_idx = 0;
  if (result.start < 0) {
    throw TestFailureException("Subarray start index is negative");
  }
  int para_idx = result.start;

  while (kw_idx < keywords.size()) {
    if (para_idx >= paragraph.size()) {
      throw TestFailureException(
          "Not all keywords are in the generated subarray");
    }
    if (para_idx >= paragraph.size()) {
      throw TestFailureException("Subarray end index exceeds array size");
    }
    if (paragraph[para_idx] == keywords[kw_idx]) {
      kw_idx++;
    }
    para_idx++;
  }
  return result.end - result.start + 1;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "paragraph", "keywords"};
  generic_test_main(argc, argv, param_names, "subsequence_cover.tsv",
                    &FindSmallestSequentiallyCoveringSubsetWrapper);
  return 0;
}
