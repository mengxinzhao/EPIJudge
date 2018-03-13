#include <vector>
#include <queue>
#include <iostream>
#include <set>
#include <utility>
#include <map>
#include <iterator>

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
bool matchHelper(int match_offset, std::pair<int,int>curr_loc, MatchStatus& curr,
                 std::map<std::pair<int,int>, MatchStatus>&tbl){

    if (curr.matches.find(match_offset) == curr.matches.end()) {
        return false;
    }
    else {
        if (match_offset-1 ==0)
            return true;
        //see if they match match_offset -1
        int i = curr_loc.first;
        int j = curr_loc.second;

        bool new_match = false;
        if (tbl.find(std::make_pair(i+1,j))!= tbl.end())
            new_match |= matchHelper(match_offset-1, std::pair<int,int>({i+1,j}),tbl.find(std::make_pair(i+1,j))->second, tbl );
        if (tbl.find(std::make_pair(i-1,j))!= tbl.end())
            new_match |= matchHelper(match_offset-1, std::pair<int,int>({i-1,j}),tbl.find(std::make_pair(i-1,j))->second, tbl );
        if (tbl.find(std::make_pair(i,j+1))!= tbl.end())
            new_match |= matchHelper(match_offset-1, std::pair<int,int>({i,j+1}),tbl.find(std::make_pair(i,j+1))->second, tbl );
        if (tbl.find(std::make_pair(i,j-1))!= tbl.end())
            new_match |= matchHelper(match_offset-1, std::pair<int,int>({i,j-1}),tbl.find(std::make_pair(i,j-1))->second, tbl );
        return new_match;
    }
    
}

bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
                              const vector<int>& pattern) {
    
    std::map<std::pair<int,int>, MatchStatus>tbl;
    
    // table constructions takes O(grid_size* pattern_size)
    for (size_t i=0;i < grid.size();i++)
        for (size_t j =0; j< grid[i].size();j++) {
            MatchStatus s = MatchStatus();
            for (size_t len =0; len < pattern.size();len++) {
                if (grid[i][j] == pattern[len]) {
                    s.update(len+1);
                }
            }
            if (!s.matches.empty())
                tbl.insert(std::make_pair(std::make_pair(i,j),s));
        }
    
    for (auto &iter:tbl) {
        if (matchHelper(pattern.size(), iter.first, iter.second,tbl))
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
