short Parity(unsigned long x) {
  // Implement this placeholder.
  int num_ones = 0;
  while (x)  {
     num_ones+= x & 0x1;
     x = x>>1;
  }
  return num_ones%2;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"x"};
  generic_test_main(argc, argv, param_names, "parity.tsv", &Parity);
  return 0;
}
