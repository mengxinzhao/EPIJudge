#include <string>
#include <unordered_map>
#include <vector>
using std::string;
using std::vector;
using std::unordered_map;

//even length string can't have char appearing more than 1 odd times
//odd length string must have all char apeparning even times
bool CanFormPalindrome(const string& s) {
    unordered_map<char, vector<int>> tbl;
    for (int i=0;i<s.length();i++) {
        tbl[s[i]].push_back(i);
    }
    if (s.length()%2) {
        //odd length at most 1 char appearing odd time
        int odd_times = 0;
        for (auto &iter: tbl){
            if (iter.second.size()%2) {
                odd_times+=1;
                if (odd_times>=2)
                    return false;
            }
        }
    }else {
        // even length. each char needs to be appearing even times
        for (auto &iter: tbl){
            if (iter.second.size()%2)
                return false;
        }
    }
  return true;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"s"};
  generic_test_main(argc, argv, param_names, "can_string_be_palindrome.tsv",
                    &CanFormPalindrome);
  return 0;
}
