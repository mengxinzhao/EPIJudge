#include <string>
#include <stack>
using std::string;

bool isPair(char c1, char c2) {
   if (c1 == '(' && c2 == ')')
     return true;
   if (c1 == '[' && c2 == ']')
     return true;
   if (c1 == '{' && c2 == '}')
    return true;

    return false;
}

bool IsWellFormed(const string& s) {
  // Implement this placeholder.
  std::stack<char> st;
  // check 0 string
  if (s.empty())
    return true;

  if (s.size() == 1)
    return false;

  st.push(s[0]);
  for (int i=1; i < s.length();i++) {
     if (!st.empty() && isPair(st.top(),s[i])) {
		 st.pop();
	 } else
		 st.push(s[i]);
  }
  // well formed string should have empty stack. All pairs are popped
  return st.empty();
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "is_valid_parenthesization.tsv", &IsWellFormed);
  return 0;
}
