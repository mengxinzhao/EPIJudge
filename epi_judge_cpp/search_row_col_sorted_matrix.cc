#include <vector>
#include <iostream>
#include <set>
using std::vector;

void print(vector<int> A) {
		for (int i=0;i< A.size();i++)
			std::cout<<A[i]<<" ";
		return ;
	}

bool MatrixSearch(const vector<vector<int>>& A, int x) {
  // Implement this placeholder.
	// row, column sorted
	if (A.empty())
		return false; // don't bother

	int row_size = A.size() ;
	int column_size = A[0].size()  ;
	int i = 0;
	int j = column_size -1 ;

	// start with top right
	while (i<=row_size-1 && j >=0) {
		if (A[i][j] == x)
			return true;
		if (A[i][j] < x) {
			// compare along y direction
			i++;
		}else if (A[i][j] > x) {
			// compare along x direction
			j--;
		}
	}
  return false;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "search_row_col_sorted_matrix.tsv",
                    &MatrixSearch);
  return  0;
}
