#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::make_unique;
using std::vector;
using std::min;

// can a case be reused after one drop and it doesn't break? yes. 
// max_safe_height(c,d)
// start droping one case from max_safe_height(c-1,d-1)+1 height. if breaks
// max_safe_height(c,d) is decided b max_safe_height(c-1,d-1). number needed
// to be tested so far= max_safe_height(c-1,d-1)+1
// if not break,the max_safe_height is decided by max_safe_height(c,d-1) // only d-1 drop left
// the number needed total max_safe_height(c-1,d-1)+1 + max_safe_height(c,d-1)
// worst case: max_safe_height(c,d)= max_safe_height(c-1,d) +1 + max_safe_height(c-1,d-1)
// base case:max_safe_height(0,d) = 0
//           max_safe_height(c,0) = 0
//           max_safe_height(1,d) = d       // one case, drop up to max d times if it doesn't break
//           max_safe_height(c,1) = 1      // c cases c>=1, drop up to 1 time only
int GetHeight(int cases, int drops) {
    
    vector<vector<int>> msf(cases+1, vector<int>(drops+1,0));
    for (int i=1;i <msf.size();i++){
        msf[i][1] = 1;
    }
    for (int i=0;i <msf[0].size();i++) {
        if (msf.size()>1)
            msf[1][i] = i;
    }

    for (int i =2; i<=cases; i++)
        for (int j=2; j<= drops;j++) {
            msf[i][j] = 1 + msf[i][j-1] + msf[i-1][j-1];
            //std::cout<<"max_safe_height: " << i<<", "<< j<< " : "<<msf[i][j]<<std::endl;
        }
    return msf[cases][drops];
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"cases", "drops"};
  generic_test_main(argc, argv, param_names, "max_safe_height.tsv", &GetHeight);
  return 0;
}
