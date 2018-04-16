#include <vector>
#include <algorithm>
#include <iostream>
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::sort;
struct Jug {
    int high;
    int low;
};
// if [510,515] jug is used in the final step, the already measured milk
// needs to be ([2100-510], [2300-515]. The last stage remain milk if not fitting the size of any
// jugs will not be feasible to measure milk.
// [L,H] feasible  = [L-550, H-515]  || || [L-290, H-310| ||  [ L- 230, H- 240]
// L,H feasible =  OR ( (L - jugs[i].low)feasible && (L - jugs[i].high) feasible) i=0...N
// use DP[L][H] = true/false indicate if a L,H range is feasible to be measured by the jugs
// DP[0][0] = true
// DP[jugs[i].high][DP[jugs[i]].low] = true for all i=0...N

bool CheckFeasible(const vector<Jug>& Jugs, int L, int H) {
    vector<vector<bool>> feasible(H+1, vector<bool>(L+1,false));
    // init

    feasible[0][0] = true;

    for (int h = 1; h<= H; h++) {
        for (int l = 1; l <= L; l++) {
            for (size_t k=0; k< Jugs.size();k++) {
                feasible[h][l] = feasible[h][l] ||( (h-Jugs[k].high>=0 && l-Jugs[k].low>=0)?  feasible[h-Jugs[k].high][l-Jugs[k].low] : false);
            }
//            if (feasible[h][l] == true)
//                std::cout<<"["<<h<<","<<l<< "]: "<<feasible[h][l]<<std::endl;
        }
    }
    return feasible[H][L];
}

template <>
struct SerializationTraits<Jug> : UserSerTraits<Jug, int, int> {};

bool operator==(const Jug& lhs, const Jug& rhs) {
  return lhs.low == rhs.low && lhs.high == rhs.high;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"jugs", "L", "H"};
  generic_test_main(argc, argv, param_names, "defective_jugs.tsv",
                    &CheckFeasible);
  return 0;
}
