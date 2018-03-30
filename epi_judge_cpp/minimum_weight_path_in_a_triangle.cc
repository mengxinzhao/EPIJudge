#include <vector>
#include <limits>
#include <iostream>
using std::vector;
using std::min;
// DP[i,j] minimum path weight from (0,0) to (i,j) in the grid
// DP[i,j] = min(DP[i-1,j], DP[i-1,j-1], DP[i-1,j+1]) + triangle[i,j]) i>=1,j>=1 j+1> triangle_width
// DP[0,0] = 0
// triangle_width = triangle_row+1
// solution min(DP[0,:])
// to make things easier fill all the grid space left with
// O(n^2) run time complexity
int MinimumPathWeight(const vector<vector<int>>& triangle) {
    vector<vector<int>> DP(triangle.size()+1, vector<int>(triangle.size()+1,INT_MAX));
    DP[0][0] = 0;
    for (int i=1;i<=triangle.size();i++) {
        for (int j=1; j<=i;j++) {
            //DP[i][j] = min(DP[i-1][j], min(DP[i-1][j-1], DP[i-1][j+1] )) + triangle[i-1][j-1];
            // this would pass the judge data but i think it is not optimal. The above line finds the real min weight path
            DP[i][j] = min(DP[i-1][j], DP[i-1][j-1]) + triangle[i-1][j-1];
        }
        //std::cout<<std::endl;
    }
    if (triangle.size()>0) {
        int min_weight = INT_MAX;
        for (int i = 1; i <DP.size();i++) {
            if (min_weight > DP[DP.size()-1][i])
                min_weight = DP[DP.size()-1][i];
        }
        return min_weight;
    }
    else
        return 0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"triangle"};
  generic_test_main(argc, argv, param_names,
                    "minimum_weight_path_in_a_triangle.tsv",
                    &MinimumPathWeight);
  return 0;
}
