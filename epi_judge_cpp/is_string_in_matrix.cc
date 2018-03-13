#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <utility>
#include <map>

using std::vector;

struct MatchStatus {
public:
    std::set <int> matches;
    
    MatchStatus():matches({}) {}

    MatchStatus &update(int new_offset) {
        if (matches.find(new_offset) == matches.end())
            matches.insert(new_offset);
        return *this;
    }
};

// When the current match_offset is matched recursively
// 4 directions in the table if match_offset is matched
// O(4^N) N: table size
// not efficient at all. worst running time when pattern is long duplication of the grid
// [[55,55,55]]  ==> patter to be searched [55,55,55,55,55...]
bool matchHelper(const vector<vector<int>>& grid,
                 const vector<int>& pattern,
                 int match_len,
                 int i, int j,
                 std::map<std::pair<int,int>, MatchStatus>&tbl){

    if (grid[i][j] == pattern[match_len-1]) {
        if ((match_len+1)>pattern.size())
            return true;
        bool new_match = false;
        if (i+1 < grid.size())
            new_match |= matchHelper(grid,pattern, match_len+1, i+1,j,tbl );
        if (i-1 >=0 )
            new_match |= matchHelper(grid,pattern, match_len+1, i-1,j,tbl );
        if (j+1 < grid[i].size())
            new_match |= matchHelper(grid,pattern, match_len+1, i,j+1,tbl );
        if (j-1 >=0)
            new_match |= matchHelper(grid,pattern, match_len+1, i,j-1,tbl );
        return new_match;
        
    }else
        return false;
    
}


bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
                              const vector<int>& pattern) {
    
    std::map<std::pair<int,int>, MatchStatus>tbl;
    
    // table constructions takes O(grid_size* pattern_size)
    size_t len =0;
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
