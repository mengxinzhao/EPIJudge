#include <vector>
#include <unordered_map>
#include <stack>
#include <memory>
#include <numeric>      // std::accumulate
#include <iostream>
using std::vector;
using std::accumulate;
using std::stack;

int EvaluateExpression(vector<char> &operators,vector<int>  &operands) {
    
    stack<int> intermediate_operands;
    int operand_idx = 0;
    intermediate_operands.push(operands[operand_idx++]);
    // Evaluates '*' first.
    for (char oper : operators) {
        if (oper == '*') {
            //std::cout<< intermediate_operands.top() << " x "<<operands[operand_idx];
            int product = intermediate_operands.top() * operands[operand_idx++];
            intermediate_operands.pop();
            intermediate_operands.push(product);
        } else {  // oper == '+'.
            //std::cout<<  " + "<<operands[operand_idx];
            intermediate_operands.push(operands[operand_idx++]);
        }
    }
    
    // Evaluates '+' second.
    int sum = 0;
    while (!intermediate_operands.empty()) {
        sum += intermediate_operands.top();
        intermediate_operands.pop();
    }
    return sum;
}

bool ExpressionSynthesisHelper(const vector<int> & digits, int i,int current_term,
               int target,vector<char> &operators, vector<int> &operands) {
    
    current_term = current_term*10 + digits[i];
    if (i==digits.size()-1) {
        operands.push_back(current_term);
        if (EvaluateExpression(operators,operands) == target)
            return true;
        operands.pop_back();
        return false;
    }
    
    // no operator merge
    if (ExpressionSynthesisHelper(digits, i+1,current_term, target, operators, operands) == true)
        return true;
    
    // try *
    operands.push_back(current_term);
    operators.push_back('*');
    if (ExpressionSynthesisHelper(digits, i+1,0, target, operators, operands) == true)
        return true;
    operands.pop_back();
    operators.pop_back();
    
    // try +
    operands.push_back(current_term);
    operators.push_back('+');
    if (ExpressionSynthesisHelper(digits, i+1,0, target, operators, operands) == true)
        return true;
    operators.pop_back();
    operands.pop_back();
    
    
    // nothing works here
    return false;
}

bool ExpressionSynthesis(const vector<int>& digits, int target) {

    vector<int>operands;
    vector<char>operators;

    return ExpressionSynthesisHelper(digits, 0, 0,target,operators,operands);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"digits", "target"};
  generic_test_main(argc, argv, param_names, "insert_operators_in_string.tsv",
                    &ExpressionSynthesis);
  return 0;
}
