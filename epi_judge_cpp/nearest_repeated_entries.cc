#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <iostream>
#include <unordered_map>

using std::string;
using std::vector;
using std::unordered_map;
using std::priority_queue;


// map each word to its the last minimum gap
// iterate through the map and get the min gap
int FindNearestRepetition(const vector<string>& paragraph) {
    unordered_map<string, int > tbl;
    int min_gap = INT_MAX;
    for(int i=0; i< paragraph.size();i++){
        if (tbl.find(paragraph[i]) == tbl.end())
            tbl[paragraph[i]] = i;
        else {
            if (min_gap >  (i-tbl[paragraph[i]]))
                min_gap = i-tbl[paragraph[i]];
            //std::cout<<paragraph[i]<<"," << i <<" min_gap:" << min_gap<<std::endl;
            tbl[paragraph[i]] = i;
        }
    }
    if (min_gap == INT_MAX)
        return -1;
    else
        return min_gap;
    
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"paragraph"};
  generic_test_main(argc, argv, param_names, "nearest_repeated_entries.tsv",
                    &FindNearestRepetition);
  return 0;
}
