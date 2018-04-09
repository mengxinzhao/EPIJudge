#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using std::string;
using std::vector;
using std::map;

// Finds the candidates which may occur > n / k times.
vector<string> SearchFrequentItems(
    int k, vector<string>::const_iterator stream_begin,
    const vector<string>::const_iterator stream_end) {
    
    map<string, int> word_count;
    vector<string> hitters;
    auto &iter = stream_begin;
    int count =0;
    while(iter!= stream_end) {
        word_count[*iter]++;
        count++;
        iter++;
    }
    iter = stream_begin;
    for (const auto & iter: word_count){
        if (iter.second > count/k )
            hitters.push_back(iter.first);
    }
    return hitters;
}

vector<string> SearchFrequentItemsWrapper(int k, vector<string>& stream) {
  return SearchFrequentItems(k, begin(stream), end(stream));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"k", "stream"};
  generic_test_main(argc, argv, param_names, "search_frequent_items.tsv",
                    &SearchFrequentItemsWrapper,
                    &UnorderedComparator<std::vector<std::string>>);
  return 0;
}
