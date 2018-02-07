
short CountBits(unsigned int x) {
  // Implement this placeholder.
  int num_bits = 0;
  while (x) {
    num_bits += x & 0x1;
    x = x>>1;
  }
  return num_bits;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "count_bits.tsv", &CountBits);
  return 0;
}
