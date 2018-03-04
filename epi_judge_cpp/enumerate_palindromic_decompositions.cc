#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cstddef>
#include <iostream>
using std::string;
using std::vector;

bool isPalindrome(const string &input, size_t start, size_t end)
{
    for (size_t i = start; i <= (start+end)/2; i++)
        if (input[i] != input[end - i])
            return false;
    return true;
}

// aabac
// a | abac|
//          --> a | a | bac
//                         --> a | a | b | ac
//                                      --> a | a | b | a | c
//          --> a | aba | c
// aa | bac
//         --> aa | b| ac
//                       --> aa | b | a | c

// recursively decomposite string as palindrom_prefix | the rest to the end of the string
void PalindromeDecompositionsHelper(const string &input,vector<string> current, vector<vector<string>> &result)
{
    if (input.empty()) {
        result.emplace_back(current);
        return ;
    }

    for (size_t prefix_length=1; prefix_length <=input.length();prefix_length++){
        if (isPalindrome(input, 0,prefix_length-1)) {
            string prefix(string(input.begin(), input.begin() +prefix_length));
            current.push_back(prefix);
            PalindromeDecompositionsHelper(string(input.begin() + prefix_length, input.end()),current,result);
            current.pop_back();
        }
    }
}

vector<vector<string>> PalindromeDecompositions(const string& input) {
  // Implement this placeholder.
    vector<vector<string>> result({});
    vector<string> current{};
    
    PalindromeDecompositionsHelper(input,current,result);
    return result;
}

bool Comp(vector<vector<string>> expected, vector<vector<string>> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return expected == result;
};

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"input"};
  generic_test_main(argc, argv, param_names,
                    "enumerate_palindromic_decompositions.tsv",
                    &PalindromeDecompositions, &Comp);
  return 0;
}
