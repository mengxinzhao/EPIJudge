#include <iostream>
#include <vector>
// count the number of moves to climb staircases
int NumberOfWaysToTop(int top, int maximum_step) {
    // Implement this placeholder.
    // NumberOfWaysToTop(N) = NumberOfWaysToTop(N-1)
    //                  + NumberOfWaysToTop(N-2) + ... + NumberOfWaysToTop(N-max_step)
    std::vector<int> sumOfStepsForStep(top+1,0);
    sumOfStepsForStep[0] = 1;
    sumOfStepsForStep[1] = 1;
    for (int i =2 ; i <=top; i++) {
        for ( int j = std::max(i-maximum_step,0);j<i && j>=0;j++)
            sumOfStepsForStep[i] += sumOfStepsForStep[j];
    }

  return sumOfStepsForStep[top];
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"top", "maximum_step"};
  generic_test_main(argc, argv, param_names,
                    "number_of_traversals_staircase.tsv", &NumberOfWaysToTop);
  return 0;
}
