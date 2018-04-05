#include <deque>
#include <vector>
#include <algorithm>
#include <iostream>
using std::deque;
using std::vector;
using std::min;
using std::max;

struct rectangle {
    int height;
    int width;
    rectangle(int _h, int _w):height(_h), width(_w) {};
    bool operator == (const rectangle &rhs) {
        return (height == rhs.height && width == rhs.width);
    }
};

// use two additinoal helper tables
// O(N*M*k) run time complexity k is the max width of square
int MaxSquareSubmatrix(const vector<vector<int>>& A) {
    // tbl[i][j]: how far can a square reach to its right and down from i,j
    vector<vector<int>> tbl(A);
    // r_tbl[i][j]: how far can a sqaure reach to its left and up from i,j
    vector<vector<int>> r_tbl(A);
    
    for (int i = A.size()-2; i>=0; i--) {
        for (int j = A[i].size()-2; j>=0;j--)
            tbl[i][j] = A[i][j]? min(tbl[i+1][j], tbl[i][j+1])+1:  0;
    }
    
    for (int i = 1; i< A.size(); i++) {
        for (int j =1; j < A[i].size();j++)
            r_tbl[i][j] = A[i][j]? min(r_tbl[i-1][j], r_tbl[i][j-1])+1:  0;
    }
    
    // loop the table first
    int max_size = 0;
    for (int i=0; i< A.size();i++) {
        for (int j=0; j < A[i].size();j++) {
            if (tbl[i][j]) {
                // check further if its bottom right can reach back
                for (int k = tbl[i][j] ; k>=1;k--){
                    int h = min(i+ k, (int)A.size())-1;
                    int w = min(j + k, (int)A[i].size())-1;
                    //std::cout<<"i,j: "<< i<<", "<<j<<" tbl: "<< tbl[i][j]<<" r_tbl: "<< r_tbl[h][w] <<std::endl;
                    if (r_tbl[h][w]>=k && k >max_size) {
                        max_size = k;
                    }
                }

            }
        }
    }
    return max_size*max_size;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "max_square_submatrix.tsv",
                    &MaxSquareSubmatrix);
  return 0;
}
