#include <stdlib.h>
#include <stack>
bool IsPalindromeNumber(int x) {
  // Implement this placeholder.
    int _x = abs(x);
    int digits = 0;
    while (_x>0) {
        digits = digits * 10 + _x %10;
        _x = _x/10;
  }

  return (digits==x);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"x"};
  generic_test_main(argc, argv, param_names, "is_number_palindromic.tsv",
                    &IsPalindromeNumber);
  return 0;
}
