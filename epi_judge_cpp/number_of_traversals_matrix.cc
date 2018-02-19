#include <iostream>
#include <vector>
using std::vector;
// NumberOfWays[N,M] = NumberOfWays[N-1,M] (coming from N-1 row, same column)
//              + NumberOfWays[N,M-1]  (coming from M-1 column, same row)
int NumberOfWays(int N, int M) {
    // Implement this placeholder.
    vector<vector<int>> ways(N,vector<int>(M,0));
    // the first row
    ways[0] = vector<int>(M,1);
    // the first column
    for (int row = 1; row < N;row++)
        ways[row][0] = 1;

    // travel
    for (int row = 1; row < N; row++)
        for (int column = 1; column< M; column++) {
            ways[row][column] += ways[row-1][column] + ways[row][column-1];
        }
    return ways[N-1][M-1];

}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"n", "m"};
  generic_test_main(argc, argv, param_names, "number_of_traversals_matrix.tsv",
                    &NumberOfWays);
  return 0;
}
