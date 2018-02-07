#include <vector>

using std::vector;

vector<vector<int>> GeneratePascalTriangle(int num_rows) {
  // Implement this placeholder.
	  if (num_rows == 0) return {};
	  if (num_rows == 1) return {{1}};
	  if (num_rows == 2 ) return {{1},{1,1}};

	  vector<vector<int>> v(num_rows,vector<int>());
	  v.push_back({1});
	  v.push_back({1,1});
	  for (int row = 2; row < num_rows; row++) {
	     v[row].resize(row+1);
	     v[row][0] = 1;
	     v[row][row] = 1;
	     for (int column = 1; column < row; column++)
	       v[row][column] = v[row-1][column-1] + v[row-1][column];
	  }
	  return v;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"num_rows"};
  generic_test_main(argc, argv, param_names, "pascal_triangle.tsv",
                    &GeneratePascalTriangle);
  return 0;
}
