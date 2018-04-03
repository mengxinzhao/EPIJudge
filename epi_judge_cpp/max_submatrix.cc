#include <deque>
#include <vector>
#include <climits>
#include <iostream>

using std::deque;
using std::vector;
using std::min;
using std::max;

struct rectangle {
    int H;
    int W;
    rectangle(int _H, int _W): H(_H),W(_W) {}
    const int size() {return W*H;}
};

// tbl[i][j] denotes the maximum rectange of 'true' ending at i,j location
int MaxRectangleSubmatrix(const vector<vector<bool>>& A) {
    int N = A.size();
    int M = A[0].size();
    vector<vector<rectangle>> tbl(N+1,vector<rectangle>(M+1, {0,0}));
    
    for (size_t i= 0; i<A.size();i++) {
        for (size_t j= 0; j<A[i].size();j++) {
            if (A[i][j])
                tbl[i+1][j+1] = {1,1};
            else
                tbl[i+1][j+1] = {0,0};
        }
    }
    // merge rectangles
    // if tbl[i][j] = 0 there is no need to merge
    // only look at tbl[i][j] = 1
    int max_size = INT_MIN;
    for (size_t i=1; i < tbl.size(); i++) {
        for (size_t j =1; j < tbl[i].size();j++){
            if (tbl[i][j].size()) {
                // upper left neighbor = 0
                if (tbl[i-1][j-1].size() == 0) {
                    // right, upper has at least one
                    if ( tbl[i-1][j].size() || tbl[i][j-1].size()) {
                        if (tbl[i-1][j].W * (tbl[i-1][j].H+1) > (tbl[i][j-1].W+1) * tbl[i][j-1].H){
                            tbl[i][j] = {tbl[i-1][j].H+1, tbl[i-1][j].W};
                        }else
                            tbl[i][j] = {tbl[i][j-1].H,tbl[i][j-1].W+1};
                    }
                }else {
                    // 4 possible conditions
                    // upper > 0 , left =0
                    if (tbl[i-1][j].size()  && !tbl[i][j-1].size()) {
                        tbl[i][j] = {1+min(tbl[i-1][j].H, tbl[i-1][j-1].H ),1 };
                    }else if (!tbl[i-1][j].size()  && tbl[i][j-1].size()) {
                        // upper = 0 , left > 0
                        tbl[i][j] = {1, 1+ min(tbl[i][j-1].W, tbl[i-1][j-1].W)};
                    }else if (tbl[i-1][j].size()  && tbl[i][j-1].size()) {
                        // the largest rectangle merged
                        // upper left, upper and left all has rectangle
                        tbl[i][j] = { 1+min(tbl[i-1][j-1].H, min(tbl[i-1][j].H, tbl[i][j-1].H)),
                            1+ min(tbl[i-1][j-1].W,min( tbl[i-1][j].W, tbl[i][j-1].W )  ) };
                    }
                }
            }
            if( tbl[i][j].size()  > max_size)
                max_size = tbl[i][j].size();
        }
    }

    for (size_t i=1; i < tbl.size(); i++) {
        for (size_t j =1; j < tbl[i].size();j++) {
            std::cout<<tbl[i][j].size()<<" ";
        }
        std::cout<<std::endl;
    }
    return max_size;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "max_submatrix.tsv",
                    &MaxRectangleSubmatrix);
  return 0;
}
