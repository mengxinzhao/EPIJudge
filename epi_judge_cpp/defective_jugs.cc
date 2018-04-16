#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::sort;
using std::set;
using std::min;
using std::max;

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
// Not a good solution at all too slow
bool CheckFeasible_DP(const vector<Jug>& Jugs, int L, int H) {
    vector<vector<bool>> feasible(H+1, vector<bool>(L+1,false));
    // init

    feasible[0][0] = true;

    for (int h = 1; h<= H; h++) {
        for (int l = 1; l <= L; l++) {
            for (size_t k=0; k< Jugs.size();k++) {
                for (int hh = 0; hh < Jugs[k].high && h+hh <=H;hh++)
                    for (int ll =0; ll< Jugs[k].low && l+ll<=L;ll++) {
                        //can be measured by one jug
                        feasible[h+hh][l+ll] =  true;
                    }
            }
        }
    }
    return feasible[H][L];
}

struct range{
    int low;
    int high;
    range(int _low, int _high):low(_low), high(_high){}
    bool operator < (const range &rhs) const {
        return (( low < rhs.low) || (low == rhs.low && high < rhs.high));
    }
};

// recursive
bool RangeFitsOneJug(int L, int H,const vector<Jug>& Jugs) {
    for (size_t i=0; i< Jugs.size();i++) {
        //std::cout<<L<<", "<< H <<std::endl;
        if (L <= Jugs[i].low && H <= Jugs[i].high)
            return true;
    }
    return false;
}


bool CheckFeasible_Recursive(const vector<Jug>& Jugs, int L, int H, set<range> & cache) {
    //std::cout<<L<<", "<< H <<std::endl;
    if (L <0|| H<0) {
        cache.emplace(L,H);
        return false;
    }
    if (cache.find({L,H})!= cache.end())
        return false;
    
    if (RangeFitsOneJug(L,H,Jugs)) {
        return true;
    }

    for (size_t i=0; i< Jugs.size();i++) {
        int ll = L-Jugs[i].low;
        int hh = H-Jugs[i].high;
        if (CheckFeasible_Recursive(Jugs, min(ll,hh), max(ll,hh),cache))
                return true;
    }
    cache.emplace(L,H);
    return false;
}

bool CheckFeasible(const vector<Jug> &Jugs, int L, int H) {
    set<range> cache;
    return CheckFeasible_Recursive(Jugs, L, H,cache);
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
