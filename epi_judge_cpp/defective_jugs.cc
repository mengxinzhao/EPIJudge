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
