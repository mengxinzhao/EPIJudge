#include <vector>
#include <unordered_map>
#include <iostream>
using std::vector;
using std::unordered_map;

// O(N) complexity
// O(3) space
// bitwise XOR
// code taken from http://www.crazyforcode.com/find-element-appears/
// difficult to think of such solutions
int FindElementAppearsOnce(const vector<int>& A) {
    int ones = 0, twos = 0, not_threes = 0;
    // ones: mask of all element appearing one times
    // twos: mask of all element appearing two times
    
    for (int i=0; i < A.size();i++) {
        twos |= ones & A[i];
        ones^=A[i];
        
        not_threes = ~(ones & twos) ;
        ones &= not_threes ;//remove x from ones
        twos &= not_threes ;//remove x from twos

    }

    return ones;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "element_appearing_once.tsv",
                    &FindElementAppearsOnce);
  return 0;
}
