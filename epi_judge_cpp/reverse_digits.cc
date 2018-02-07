#include <stdlib.h>
long Reverse(int x) {
  // Implement this placeholder.
  long sign = (x<0)? (-1):1;
  long _x = labs(x);
  long digits = 0;
  while(_x) {
    digits = digits*10 + _x%10;
    _x = _x/10;
  }
  digits *= sign;
  return digits;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"x"};
  generic_test_main(argc, argv, param_names, "reverse_digits.tsv", &Reverse);
  return 0;
}
