#include <string>
#include <vector>
#include <functional>
#include <cstddef>
#include <algorithm>
#include <map>
#include <utility>
#include <iostream>
using std::string;
using std::vector;
using std::pair;
using std::map;

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
  // Implement this placeholder.
    vector<pair<size_t, int>> tbl;   // map hush back to index
    vector<vector<string>> result;
    for (size_t len = 0; len < dictionary.size();len++) {
        size_t val = HushString(dictionary[len]);
        tbl.push_back(std::make_pair(val,len));
    }

    std::sort(tbl.begin(), tbl.end(), compare_hush);
    vector<string> current;
    // grab the string that its hush value appear at twice in the array
    for (size_t len = 0; len < tbl.size()-1;len++) {
        current.push_back(dictionary[tbl[len].second]);
        if (tbl[len].first != tbl[len+1].first) {
            result.push_back(current);
            current.clear();
        }
    }
    if (tbl[tbl.size()-1].first == tbl[tbl.size()-2].first ) {
        current.push_back(dictionary[tbl[tbl.size()-1].second]);
        result.push_back(current);
    }
    // delete
    for (int i=0; i< result.size();i++) {
        if (result[i].size() <2) {
            result.erase(result.begin()+i);
            i--;
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
