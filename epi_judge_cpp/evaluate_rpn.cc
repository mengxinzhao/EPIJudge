#include <string>

using std::string;
#include <stack>
#include <ratio>
#include <iostream>

bool is_operator(char c) {
	return (c=='+' || c=='-'||c=='*'||c=='/');
}

int string_to_int(string &str) {
	// there should be no sign
	// string 4 5 6
	// index  0 1 2
	int number = 0;
	int k = str.find_first_of(',');
	if (k < 0)
		k = 0;
	for (int i=k; i < str.length();i++){
		 number = number*10 + str[i]-'0';
	}
	return number;
}

int Evaluate(const string& expression) {
  // Implement this placeholder.
	std::stack<int> tmp_result;

	for (int i=0; i< expression.length();i++) {

		if (is_operator(expression[i])) {
			int a = tmp_result.top();
			tmp_result.pop();
			int b = tmp_result.top();
			tmp_result.pop();

			switch (expression[i]) {
				case '+':
					tmp_result.push(b+a);
					break;
				case '-':
					tmp_result.push(b-a);
					break;
				case '*':
					tmp_result.push(b*a);
					break;
				case '/':
					tmp_result.push(b/a);
					break;
				default:
					break;
			}
			i++;

		}else {
			int k = string(expression.begin()+i,expression.end()).find_first_of(',');
			if (k < 0) {
				// this is need. the ending char always need to be operator
				string num_str= string(expression.begin()+i,expression.end());
				tmp_result.push(string_to_int(num_str));
				i = expression.length()-1;
			}else {
				string num_str= string(expression.begin()+i,expression.begin()+k+i);
				tmp_result.push(string_to_int(num_str));
				i = k+i;
			}
		}

	}
  return tmp_result.top();
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"expression"};
  generic_test_main(argc, argv, param_names, "evaluate_rpn.tsv", &Evaluate);
  return 0;
}
