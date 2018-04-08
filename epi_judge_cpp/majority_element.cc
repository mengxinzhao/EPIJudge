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

string MajoritySearchWrapper(const vector<string>& stream) {
  return MajoritySearch(cbegin(stream), cend(stream));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"stream"};
  generic_test_main(argc, argv, param_names, "majority_element.tsv",
                    &MajoritySearchWrapper);
  return 0;
}
