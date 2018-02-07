#include <iostream>
unsigned long SwapBits(unsigned long x, int i, int j) {
    //std::cout<<"swapping bits " <<i <<" " <<j<<std::endl;
    unsigned long mask = ~((1UL<<i)|(1UL<<j));
    x= (x & mask)| ((x >> i )& 0x1 )<< j | ((x >>j) & 0x1) <<i;
    return x;
}

unsigned long ClosestIntSameBitCount(unsigned long x) {
  // Implement this placeholder.
    unsigned long mask = 0b01;
    int idx=0,i=-1,j=-1;

    if (x == 0 ) return 0;
    unsigned long _x = x;
    while (_x) {
        // x[idx+1:idx] = 0b01 or x[idx+1:idx] = 0b10 swap the 2 digit
        if (((_x ^ mask) & 0x3)== 0 ||((_x ^ mask)&0x3)==3 ){
            i = idx;
            j = idx+1;
            break;
        }
        _x = _x>>1;
        idx++;
    }

    return SwapBits(x,i,j);

}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"x"};
  generic_test_main(argc, argv, param_names, "closest_int_same_weight.tsv",
                    &ClosestIntSameBitCount);
  return 0;
}
