#include <vector>
#include <unordered_map>
using std::vector;

bool hasDuplicates(const vector<int> &v ) {
 std::unordered_map<int,int> map;
  for (int i =0;i<v.size();i++) {
    if  (v[i]!= 0) {
      if (map.find(v[i])!= map.end())
		return true;
      else
        map.insert({v[i],i});
    }
  }
  return false;
}
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  // Implement this placeholder.
  // check on row
  for (int i = 0; i <9 ; i++) {
    if (hasDuplicates(partial_assignment[i]) )
      return false;
  }
  // check on column
  for (int c = 0; c < 9; c++) {
    vector<int> partial({partial_assignment[0][c],partial_assignment[1][c],partial_assignment[2][c],
                         partial_assignment[3][c],partial_assignment[4][c],partial_assignment[5][c],
                         partial_assignment[6][c],partial_assignment[7][c],partial_assignment[8][c]});
    if (hasDuplicates(partial) )
      return false;
  }
  // check on 3 x 3 matrix
  for (int i = 0; i < 9; i+=3)
    for (int j = 0; j < 9; j+=3) {
    vector<int> partial ({partial_assignment[i][j],partial_assignment[i][j+1],partial_assignment[i][j+2],
                          partial_assignment[i+1][j],partial_assignment[i+1][j+1],partial_assignment[i+1][j+2],
                          partial_assignment[i+2][j],partial_assignment[i+2][j+1],partial_assignment[i+2][j+2]} );
      if (hasDuplicates(partial) )
        return false;

  }
  return true;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "is_valid_sudoku.tsv", &IsValidSudoku);
  return 0;
}
