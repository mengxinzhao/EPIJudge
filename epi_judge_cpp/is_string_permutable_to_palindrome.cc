#include <string>
#include <unordered_map>
#include <vector>
using std::string;
using std::vector;
using std::unordered_map;

//even length string can't have char appearing more than 1 odd times
//odd length string must have all char appearing even times
bool CanFormPalindrome(const string& s) {
    unordered_map<char, int> tbl;
    for (int i=0;i<s.length();i++) {
        tbl[s[i]]++;
    }
    // at the most one char appearing odd times
    int count = 0;
    for (auto &iter: tbl) {
        if (iter.second %2 )
            count++;
    }
    if (s.length()%2) {
        return count <=1;
    }else {
        return count ==0;
    }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"s"};
  generic_test_main(argc, argv, param_names, "can_string_be_palindrome.tsv",
                    &CanFormPalindrome);
  return 0;
}
