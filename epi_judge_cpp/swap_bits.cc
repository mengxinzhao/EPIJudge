#include <iostream>
long SwapBits(long x, int i, int j) {
  // Implement this placeholder.
   long mask = ~((1L<<i)|(1L<<j));
    x= (x & mask)| ((x >> i )& 0x1 )<< j | ((x >>j) & 0x1) <<i;
    return x;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"x", "i", "j"};
  generic_test_main(argc, argv, param_names, "swap_bits.tsv", &SwapBits);
  return 0;
}
