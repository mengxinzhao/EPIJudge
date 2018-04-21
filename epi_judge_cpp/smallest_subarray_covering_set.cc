#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <climits>
#include <iostream>
#include <list>
#include <algorithm>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::string;
using std::unordered_set;
using std::vector;
using std::unordered_map;
using std::min;
using std::list;
using std::prev;

struct Subarray {
  int start, end;
};


struct Location {
    int start, end;
    int length;
};

// O(N*M) time: N: number of words in paragraph, M: number of words in keywords
Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords) {
    // track the  appearing loc for each keyword
    unordered_map<string, int> cache;
    Location  min_length = {.length = INT_MAX};
    for (int i=0;i< paragraph.size();i++) {
        if (keywords.find(paragraph[i]) != keywords.end()) {
            cache[paragraph[i]] = i;
        }
        int min_loc = INT_MAX;
        if (cache.size() == keywords.size()) {
            for (auto  &iter: cache) {
                if (min_loc > iter.second)
                    min_loc = iter.second;
            }
            if (min_length.length > i - min_loc) {
                min_length = {min_loc, i, i-min_loc};
            }
        }
    }

  return {min_length.start,min_length.end};
}

// O(N) time: N: number of words in paragraph
// Theoretically it should be faster but when it runs
// it doesn't beat the first one.
// I think the cost of doing more complicated data structure overweighs the performance when
// the keyword numbers are not that many
Subarray FindSmallestSubarrayCoveringSet_List(
         const vector<string> &paragraph, const unordered_set<string> &keywords) {
    
    list<int> loc; // track location of each element in the keywords. the head is latest starting point
    // track the latest starting point of each keyword
    unordered_map<string, list<int>::iterator> cache;
    
    int  min_length = INT_MAX;
    Subarray result = {0,0};
    for (int i=0;i< paragraph.size();i++) {
        if (keywords.find(paragraph[i]) != keywords.end()) {
            if ( cache.find(paragraph[i])!= cache.end()) {
                // erase the previous location
                loc.erase(cache[paragraph[i]]);
            }
            // update to the latest location
            loc.emplace_back(i);
            cache[paragraph[i]]  = prev(loc.end());
            
            if (cache.size() == keywords.size()) {
                if (min_length > loc.back() - loc.front() ){
                    result = {loc.front(), loc.back()};
                    min_length = loc.back() - loc.front() ;
                }
            }
        }
    }
    return result;
}


int FindSmallestSubarrayCoveringSetWrapper(
    TestTimer &timer, const vector<string> &paragraph,
    const unordered_set<string> &keywords) {
  unordered_set<string> copy = keywords;

  timer.Start();
  auto result = FindSmallestSubarrayCoveringSet(paragraph, keywords);
  timer.Stop();

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end) {
    throw TestFailureException("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++) {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty()) {
    throw TestFailureException("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char *argv[]) {
  std::vector<std::string> param_names{"timer", "paragraph", "keywords"};
  generic_test_main(argc, argv, param_names,
                    "smallest_subarray_covering_set.tsv",
                    &FindSmallestSubarrayCoveringSetWrapper);
  return 0;
}
