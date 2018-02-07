#include <vector>

using std::vector;

void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
	// Implement this placeholder.
	// extra room to copy the original matrix
	vector<vector<int>> &v = *square_matrix_ptr;
	vector<vector<int>> copy(v);
	int N = copy.size();  //row
	// need to take care of the empty matrix
	if  (N <= 0)
		return ;

	int M = copy[0].size(); // column
	v.resize(M);
	// 1  2  3  4
	// 5  6  7  8
	// 9 10 11 12
	//
	// 9   5  1
	// 10  6  2
	// 11  7  3
	// 12  8  4

	// N = 4, M = 3
	for (int i = 0; i < N; i++) {
		v[i].resize(N);
		for (int j = 0; j < M; j++) {
			v[j][M - i - 1] = copy[i][j];
		}
	}
  return;
}



vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> m) {
  RotateMatrix(&m);
  return m;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "matrix_rotation.tsv", &RotateMatrixWrapper);
  return 0;
}
