#include <vector>
#include <climits>
#include <algorithm>

using std::vector;
using std::min;
using std::max;

//DP[i,j] max sum when current coin head is i, coin tail is j
// S is as smart as F so S chooses the max number that leaves F the worst choice
// in each round given current head i, tail j
// if F chooses i, S chooses max(i+1,j), F has the worse choices between (i+2,j)(S chooses i+1) or (i+1, j-1) (S chooses j)
// if F chooses j, S chooses max(i,j-1) , F has the worse choices between (i+1, j-1) (S choose i) or (i,j-2) (S chooses j-1)
// F needs to choose the max (coin[i] + min(DP[i+2,j], DP[i+1][j-1], coin[j] + min(DP[i+1][j-1], DP[i][j-2]))
// when i meets j
// F choose coins [i]  i==j
//   or max(coins [i],coin[j])  i==j-1
// solution DP[0][last]
//
int MaximumRevenue( vector<int>& coins) {
    vector<vector<int>> DP(coins.size(),vector<int>(coins.size(),0));
    for (int gap = 0; gap < coins.size();gap++) {
        for (int i =0,j=gap; j<coins.size();i++,j++) {
            int A = (i+2 <= j)?DP[i+2][j]:0;
            int B = (i+1<=j-1)? DP[i+1][j-1]:0;
            int C = (i<=j-2)?DP[i][j-2]:0;
            DP[i][j] = max(coins[i] + min(A,B), coins[j]+ min(B,C) );
        }
    }
    return DP[0][coins.size()-1];
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"coins"};
  generic_test_main(argc, argv, param_names, "picking_up_coins.tsv",
                    &MaximumRevenue);
  return 0;
}
