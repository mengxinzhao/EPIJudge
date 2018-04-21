#include <string>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <utility>
#include <iostream>
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::min;
using std::pair;
using std::next;

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


// O(n) time running time
// almost bellman-ford shortest path algorithm
// the difference is that each node needs to be sequential hop from i-1 to i and each node i
// has one edge to the next i+1. thus  no outer loop in bellman-ford's algorithm
// shortest_dist [i] = shortest_dist[i-1] +loc_cache[i] - loc_cache[i-1]
Subarray FindSmallestSequentiallyCoveringSubset_Linear(
     const vector<string>& paragraph, const vector<string>& keywords){
    int start;
    int end;
    int min_length = INT_MAX;
    unordered_map<string, int> kw_cache;// map each key word to its location
    // keyword's latest occurance in paragraph
    vector<int> loc_tracker(keywords.size(), -1) ;
    // shortest length for distance from keyword 0 to  keyword i
    vector<int> shortest_dist(keywords.size(), INT_MAX);
    
    for (int i=0; i< keywords.size();i++)
        kw_cache[keywords[i]] = i;
    
    for (int i=0; i< paragraph.size();i++) {
        if (kw_cache.find(paragraph[i])!= kw_cache.end()) {
            //std::cout<<"checking ..."<<paragraph[i] << " @" << i <<std::endl;
            int expected_loc = kw_cache[paragraph[i]];
            // update location
            loc_tracker[expected_loc] =i;
            if (expected_loc == 0)
                shortest_dist[0] =1;
            else if (shortest_dist[expected_loc-1]!= INT_MAX){
                shortest_dist [expected_loc] = shortest_dist[expected_loc-1] + loc_tracker[expected_loc]  - loc_tracker[expected_loc-1];
                //std::cout<<"shortest to  ..."<<keywords[expected_loc]<< " = " << shortest_dist [expected_loc]  <<std::endl;
            }

            if (expected_loc ==keywords.size()-1) {
                if (shortest_dist [expected_loc] < min_length) {
                    min_length = shortest_dist[expected_loc];
                    start = loc_tracker[expected_loc] - shortest_dist [expected_loc]+1;
                    end = loc_tracker[expected_loc];
                    //std::cout<<"shortest to  ..."<<keywords[expected_loc]<< " start: " <<start<<" end: "<<end <<std::endl;
                }
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
