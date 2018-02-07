#include <string>

using std::string;

bool isLetterOrNumber(char c) {
	if ((c>='A' && c<='Z') || (c>='a' && c<='z'))
		return true;
	else if (c>='0' && c<='9')
		return true;
    return false;
}


bool IsPalindrome(const string& s) {
  // Implement this placeholder.
  int start = 0;
  int end = s.length()-1;
  while(start<=end) {
	  while(!isLetterOrNumber(s[start]))
		  start++;
	  while(!isLetterOrNumber(s[end]))
		  end--;
	  // start and end could go over shoot too
	  if (start >=end)
		  break;
	  if (tolower(s[start])!=tolower(s[end]))
		  return false;
	  else{
		  start++;
		  end--;
	  };
  }
  return true;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"s"};
  generic_test_main(argc, argv, param_names,
                    "is_string_palindromic_punctuation.tsv", &IsPalindrome);
  return 0;
}
