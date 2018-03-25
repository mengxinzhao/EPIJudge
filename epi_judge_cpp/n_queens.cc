#include <algorithm>
#include <iterator>
#include <vector>

using std::vector;

bool loc_exist(int curr_loc, int curr_row,vector<int>existing_loc) {
    if (find(existing_loc.begin(),existing_loc.end(),curr_loc) != existing_loc.end())
        return true;
    else {
        // check if it leads to a diagnal attacking position
        for (int i=0;i<existing_loc.size();i++) {
            if (std::abs(curr_loc - existing_loc[i]) == std::abs(curr_row-i))
                return true;
        }
        
    }
    return false;
}

// kth row to be filled
void NQueensHelper(vector<vector<int>> &result, vector<int>current, int k, int n) {
    if (k>=n ) {
        // have a solution
        if (current.size() == n)
            result.push_back(current);
        return;
    }
    int curr_choice = current.back();
    for (int i=0;i<n;i++) {
        vector<int> copy = current;
        if (!loc_exist(i,k, copy)) {
            copy.push_back(i);
            NQueensHelper(result,copy,k+1,n);
        }
    }
}
vector<vector<int>> NQueens(int n) {
    vector<vector<int>> result;
    for (int i=0;i<n;i++) {
        NQueensHelper(result,vector<int>({i}),1,n);
    }
    return result;
}

bool Comp(vector<vector<int>>& a, vector<vector<int>>& b) {
  std::sort(std::begin(a), std::end(a));
  std::sort(std::begin(b), std::end(b));
  return a == b;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"n"};
  generic_test_main(argc, argv, param_names, "n_queens.tsv", &NQueens, &Comp);
  return 0;
}
