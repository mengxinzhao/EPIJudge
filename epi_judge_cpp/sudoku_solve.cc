#include <algorithm>
#include <cmath>
#include <iterator>
#include <vector>
#include <unordered_map>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::begin;
using std::end;
using std::vector;

bool find_unassigned_location(vector<vector<int>> *partial_assignment,int &row, int &col) {
    for (row =0; row< (*partial_assignment).size();row++)
        for (col = 0; col < (*partial_assignment)[row].size();col++)
            if ((*partial_assignment)[row][col] == 0)
                return true;
    return false;
}

bool no_conflicts(vector<vector<int>> *partial_assignment, int row, int col, int num) {
    // can't be appearing twice in a row, col or 3 x 3 box
    
    // check row
    for(int i=0; i < (*partial_assignment).size();i++) {
        if ((*partial_assignment)[i][col]!=0 && (*partial_assignment)[i][col]==num ) {
                return false;
        }
    }

    // check column
    for(int i=0; i < (*partial_assignment)[row].size();i++) {
        if ((*partial_assignment)[row][i]!=0 && (*partial_assignment)[row][i]==num ) {
            return false;
        }
    }
    
    // check 3 x 3
    int row_start = 3*(int)(row/3);
    int column_start = 3 * (int)(col/3);
    for (int i = row_start; i< row_start + 3; i++)
        for (int j= column_start; j< column_start+3; j++) {
            if ((*partial_assignment)[i][j] == num )
                return false;
        }
    
    return true;
}
//solve using materials https://see.stanford.edu/materials/icspacs106b/H19-RecBacktrackExamples.pdf
bool SolveSudoku(vector<vector<int>>* partial_assignment) {
    int row, col;
    // all filled. success
    if (!find_unassigned_location(partial_assignment, row, col))
        return true;
    
    for (int num=1; num<=9;num++) {
        if (no_conflicts(partial_assignment, row,col, num)) {
            // try one choice
            (*partial_assignment)[row][col] = num;
            // go on to the next location
            if (SolveSudoku(partial_assignment))
                return true;
            // failure. backout assignment. try again
            (*partial_assignment)[row][col] = 0;
            
        }
    }
    return false;   // this trigger failure and  back tracking
}

vector<int> GatherColumn(const vector<vector<int>>& data, size_t i) {
  vector<int> result;
  for (auto& row : data) {
    result.push_back(row[i]);
  }
  return result;
}

vector<int> GatherSquareBlock(const vector<vector<int>>& data,
                              size_t block_size, size_t n) {
  vector<int> result;
  size_t block_x = n % block_size;
  size_t block_y = n / block_size;
  for (size_t i = block_x * block_size; i < (block_x + 1) * block_size; i++) {
    for (size_t j = block_y * block_size; j < (block_y + 1) * block_size; j++) {
      result.push_back(data[i][j]);
    }
  }

  return result;
}

void AssertUniqueSeq(const vector<int>& seq) {
  vector<bool> seen(seq.size(), false);
  for (auto& x : seq) {
    if (x == 0) {
      throw TestFailureException("Cell left uninitialized");
    }
    if (x < 0 || x > seq.size()) {
      throw TestFailureException("Cell value out of range");
    }
    if (seen[x - 1]) {
      throw TestFailureException("Duplicate value in section");
    }
    seen[x - 1] = true;
  }
}

void SolveSudokuWrapper(TestTimer& timer,
                        const vector<vector<int>>& partial_assignment) {
  vector<vector<int>> solved = partial_assignment;

  timer.Start();
  SolveSudoku(&solved);
  timer.Stop();

  if (!std::equal(begin(partial_assignment), end(partial_assignment),
                  begin(solved), end(solved), [](auto br, auto cr) {
                    return std::equal(begin(br), end(br), begin(cr), end(cr),
                                      [](int bcell, int ccell) {
                                        return bcell == 0 || bcell == ccell;
                                      });
                  }))
    throw TestFailureException("Initial cell assignment has been changed");

  auto block_size = static_cast<size_t>(sqrt(solved.size()));

  for (size_t i = 0; i < solved.size(); i++) {
    AssertUniqueSeq(solved[i]);
    AssertUniqueSeq(GatherColumn(solved, i));
    AssertUniqueSeq(GatherSquareBlock(solved, block_size, i));
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "partial_assignment"};
  generic_test_main(argc, argv, param_names, "sudoku_solve.tsv",
                    &SolveSudokuWrapper);
  return 0;
}
