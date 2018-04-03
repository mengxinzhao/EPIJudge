#include <vector>
#include <climits>
#include <stack>
#include <algorithm>
#include <iostream>
using std::vector;
using std::stack;
using std::max;

// use stack to track increasing height index
// right, left to track the range a certain height can cover
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
    return max_size;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"heights"};
  generic_test_main(argc, argv, param_names,
                    "largest_rectangle_under_skyline.tsv",
                    &CalculateLargestRectangle);
  return 0;
}
