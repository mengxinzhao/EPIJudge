#include <vector>
#include <iostream>
using std::vector;
// C(n,k) = C(n-1,k) + C(n-1,k-1)
// C(n,k) = C(n, n-k)
int ComputeBinomialCoefficient(int n, int k) {
    // Implement this placeholder.

    vector<vector<int>> C(n+1,vector<int>(n/2+1,0));
    // all C(n,0) = 1
    C[0][0] = 1;
    for (int row = 1 ; row <=n;row++) {
        C[row][0] = 1;
        for (int column = 1; column <= row/2; column++) {
            C[row][column] = ((column > (row-1)/2)? C[row-1][ row-1 - column] : C[row-1][column]) + C[row-1][column-1];
        }
    }
    if (k > n/2)
        k = n - k ;
    return C[n][k];
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"n", "k"};
  generic_test_main(argc, argv, param_names, "binomial_coefficients.tsv",
                    &ComputeBinomialCoefficient);
  return 0;
}
