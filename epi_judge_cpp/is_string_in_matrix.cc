#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <utility>
#include <map>
#include <tuple>
#include <unordered_set>

using std::vector;
using std::tuple;
using std::get;
using std::unordered_set;
using std::hash;
using std::set;

struct MatchStatus {
    int x, y;   // start location
    int match_distance ;// max distance in the pattern it can be matched starting from x,y
};


//struct HashTuple {
//    size_t operator()(const tuple<int, int, int>& t) const {
//        return hash<int>()(get<0>(t) ^ get<1>(t) * 1021 ^ get<2>(t) * 1048573);
//    }
//};

// When the current match_offset is matched recursively
// 4 directions in the table if match_offset is matched
// O(4^N) N: table size
// not efficient at all. worst running time when pattern is long duplication of the grid
// [[55,55,55]]  ==> patter to be searched [55,55,55,55,55...]
// use a cached table to store all the unmatched location
bool matchHelper(const vector<vector<int>>& grid,
                 const vector<int>& pattern,
                 int match_len,
                 int i, int j,
                 set<tuple<int,int,int>> &tbl){

    
    if (pattern.size () < match_len)
        return true;
    if (i < 0 || i >=grid.size() || j < 0 || j >=grid[i].size() ||
        tbl.find({i, j, match_len}) != tbl.cend() ||
        grid[i][j] != pattern[match_len-1]) {
        return false;
    }
    if (matchHelper(grid,pattern, match_len+1, i+1,j,tbl )||matchHelper(grid,pattern, match_len+1, i-1,j,tbl)
            ||matchHelper(grid,pattern, match_len+1, i,j+1,tbl )|| matchHelper(grid,pattern, match_len+1, i,j-1,tbl ))
        return true;
        
    tbl.emplace(i,j,match_len);
    return false;
    
}


bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
                              const vector<int>& pattern) {
    // use just set is faster instead of unordered_set with customer hash
    set<tuple<int,int,int>>tbl;
    
    for (size_t i=0;i < grid.size();i++)
        for (size_t j =0; j< grid[i].size();j++) {
            if (matchHelper(grid,pattern,1,i,j,tbl))
                return true;
    }
    

    return false;
}


#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"grid", "pattern"};
  generic_test_main(argc, argv, param_names, "is_string_in_matrix.tsv",
                    &IsPatternContainedInGrid);
  return 0;
}
