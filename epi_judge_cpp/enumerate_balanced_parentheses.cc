#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <set>
using std::string;
using std::vector;

void GenerateBalancedParenthesesHelper(int start, int num_pairs, string &current, std::set<string> & result) {
    if (start >=num_pairs)
        return ;
    for (int k = start; start < num_pairs; start ++)
        for (int i=start+1; i<num_pairs; i++) {
            if (current[start*2+1]!=current[2*i]) {
                std::swap(current[start*2+1],current[2*i]);
                //std::cout<<current<<std::endl;
                result.insert(current);
                GenerateBalancedParenthesesHelper(start+1, num_pairs,current,result);
                std::swap(current[start*2+1],current[2*i]);
            }
    }
}

vector<string> GenerateBalancedParentheses(int num_pairs) {
  // Implement this placeholder.
  
    vector<string> result{};
    if (num_pairs == 0)
        return {("")};
    string first{};
    std::set<string> result_set;
    for (int i=0;i< num_pairs;i++)
        first.insert(0,"()");
    result_set.insert(first);
    GenerateBalancedParenthesesHelper(0,num_pairs,first, result_set);
    for (auto &e:result_set)
        result.push_back(e);
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


