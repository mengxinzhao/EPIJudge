#include <string>
#include <vector>
#include <map>
#include <iostream>
using std::string;
using std::vector;
using std::map;

string MajoritySearch(vector<string>::const_iterator stream_begin,
                      const vector<string>::const_iterator stream_end) {
    map<string, int> words_count;
    map<int, string> count_words;
    auto &iter = stream_begin;
    while(iter!= stream_end) {
        words_count[*iter]++;
        count_words[words_count[*iter]++] = *iter;
        iter++;
    }
    
    return count_words.rbegin()->second;
}

// use greedy search
// problem statement guarantees there is a majority element >1/2. M/N > 1/2
// each time if we throw a pair of distinct element out they could be all minority: M/N-2 > 1/2
// one majority one minority  M-1/N-2. both > 1/2
// we keep throwing all pairs of distinct element out  what's left is the majority element
string MajoritySearch_Greedy(vector<string>::const_iterator stream_begin,
                      const vector<string>::const_iterator stream_end) {
    int count =0; // to track distinct pair of elements
    auto &iter = stream_begin;
    string word;
    while(iter!= stream_end) {
        if (count ==0) {
            word = *iter;
            count= 1;
        }else if (word == *iter)
            count++;
        else
            count--;
        iter++;
    }
    return word;
}

string MajoritySearchWrapper(const vector<string>& stream) {
  return MajoritySearch_Greedy(cbegin(stream), cend(stream));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"stream"};
  generic_test_main(argc, argv, param_names, "majority_element.tsv",
                    &MajoritySearchWrapper);
  return 0;
}
