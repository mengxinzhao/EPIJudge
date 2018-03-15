#include <string>
#include <vector>
#include <functional>
#include <cstddef>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <iostream>
using std::string;
using std::vector;
using std::pair;
using std::unordered_map;

struct Compare {
    bool operator() (pair<size_t, int> &one ,pair<size_t, int> &two) {
        return one.first < two.first;
    }
}compare_hush;

// sort the string and then hash
// tbl lbt will have the same sorted value blt
size_t HushString (string item ){
    size_t result = 0UL;
    string & str = item;
    std::sort(str.begin(),str.end());
    result =std::hash<string>()(str) ;
    return result;
}


vector<vector<string>> FindAnagrams( const vector<string>& dictionary) {
    unordered_map<size_t, vector<int>> tbl;   // map hush back to index
    vector<vector<string>> result;
    for (size_t len = 0; len < dictionary.size();len++) {
        size_t val = HushString(dictionary[len]);
        tbl[val].push_back(len);
    }
    
    for (auto &iter: tbl) {
        if (iter.second.size()>=2){
            vector<string> current;
            for (auto &index: iter.second) {
                current.push_back(dictionary[index]);
            }
            result.push_back(current);
        }
    }

    return result;
    
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"dictionary"};
  generic_test_main(
      argc, argv, param_names, "anagrams.tsv", &FindAnagrams,
      &UnorderedComparator<std::vector<std::vector<std::string>>>);
  return 0;
}
