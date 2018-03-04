#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using std::string;
using std::vector;

void GenerateBalancedParenthesesHelper(int num_left_left, int num_right_left, string current, vector<string> & result) {
    
    if (num_left_left == 0 && num_right_left == 0) {
        result.push_back(current);
        return;
    }

    if (num_left_left == 0 && num_right_left > 0) {
        // only can insert ')'
        current.insert(current.end(),')');
        GenerateBalancedParenthesesHelper(num_left_left,num_right_left-1, current,result);
    }else if (num_left_left == num_right_left) {
        // when number of left parens and right parens are matching choose left
        current.insert(current.end(),'(');
        GenerateBalancedParenthesesHelper(num_left_left-1,num_right_left, current,result);
    }else {
        // can choose '(' or ')'
        //
        string left_insert = current;
        left_insert.insert(left_insert.end(),'(');
        GenerateBalancedParenthesesHelper(num_left_left-1,num_right_left, left_insert,result);
        
        string right_insert = current;
        right_insert.insert(right_insert.end(),')');
        GenerateBalancedParenthesesHelper(num_left_left,num_right_left-1, right_insert,result);
    }
    return;

}

vector<string> GenerateBalancedParentheses(int num_pairs) {
    // Implement this placeholder.
    
    vector<string> result{};
    string current = {""};
    GenerateBalancedParenthesesHelper(num_pairs, num_pairs, current, result);
    return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"num_pairs"};
  generic_test_main(
      argc, argv, param_names, "enumerate_balanced_parentheses.tsv",
      &GenerateBalancedParentheses, &UnorderedComparator<vector<string>>);
  return 0;
}


