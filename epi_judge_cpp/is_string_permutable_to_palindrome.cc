#include <string>

using std::string;

bool CanFormPalindrome(const string& s) {
  // Implement this placeholder.
  return true;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"s"};
  generic_test_main(argc, argv, param_names, "can_string_be_palindrome.tsv",
                    &CanFormPalindrome);
  return 0;
}
