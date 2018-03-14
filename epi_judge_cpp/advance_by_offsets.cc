#include <vector>
#include <iostream>
#include <cstddef>
#include <algorithm>

using std::vector;

//O(N^2) complexity
//O(N) space
bool CanReachEnd(const vector<int>& max_advance_steps) {
    vector<int> tbl(max_advance_steps.size(),0);
    tbl[0]=1;

    size_t max_step = *std::max_element(max_advance_steps.begin(), max_advance_steps.end());
    max_step = std::min(max_advance_steps.size(),max_step);
    // build up the cache
    // reachable(i,j) = reachable(i,j-step) && max_advance_steps[j-step] >= step
    for (size_t i =1 ; i < max_advance_steps.size();i++) {
        int max_distance = std::min(i,max_step);
        for (int step = 1 ; step <=max_distance;step++) {
            tbl[i] += (tbl[i-step] > 0 && max_advance_steps[i-step] >= step);
            //std::cout<<"step: "<< step << " 0 to "<<i <<" through "<< i-step << " reachable: "<<tbl[i] << std::endl;
        }
    }
    return tbl[max_advance_steps.size()-1];

}



#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"max_advance_steps"};
  generic_test_main(argc, argv, param_names, "advance_by_offsets.tsv",
                    &CanReachEnd);
  return 0;
}
