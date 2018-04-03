#include <algorithm>
#include <cassert>
#include <deque>
#include <iostream>
#include <limits>
#include <random>
#include <vector>
#include <stack>

using std::deque;
using std::vector;
using std::min;
using std::max;
using std::stack;

int CalculateLargestRectangle(const vector<int>& heights) {
    int left =0, right = 0;
    int max_size = 0;
    
    if (heights.empty())
        return 0;
    
    stack<int> stk;
    while (right < heights.size()) {
        if ( stk.empty() || heights[right] >= heights[stk.top()]) {
            stk.push(right);
            right++;
            
        }else {
            while(!stk.empty() &&  heights[right] <  heights[stk.top()]){
                int index = stk.top();
                stk.pop();
                left =  stk.empty()? -1 : stk.top();
                max_size = max(max_size, heights[index] * (right  - left - 1));
            }
        }
    }
    while(!stk.empty()) {
        int index = stk.top();
        stk.pop();
        left =  stk.empty()? -1 : stk.top();
        max_size = max(max_size, heights[index] * (right  - left - 1));
    }
    //std::cout<<"left: "<< left+1<< " right: "<< right<<std::endl;
    return max_size;
}

// use largest rectangle in skyline algorithm
// calculate the largest rectangle for the 1st row
// add the next row to form histgram, calculate the largest rectangle again
// do this when all rows are visited
// O(NxM) N row size, M colume size
int MaxRectangleSubmatrix3(const vector<vector<bool>>& A) {
    if (A.empty())
        return 0;
    
    vector<int> row_data(A[0].size(),0);
    int max_size = INT_MIN;
    for (int row = 0; row < A.size();row++) {
        for (int col =0; col <A[row].size();col++) {
            if (A[row][col])
                row_data[col] += 1;
            else
                row_data[col] = 0;
        }
        max_size = max(max_size, CalculateLargestRectangle(row_data));
    }
    return max_size;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "max_submatrix.tsv",
                    &MaxRectangleSubmatrix3);
  return 0;
}
