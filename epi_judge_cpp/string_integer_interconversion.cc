#include <string>
#include <algorithm>
#include <iostream>

#include "test_framework/test_failure_exception.h"

using std::string;

string IntToString(int x) {
  // Implement this placeholder.
  // number: -512
  // string: - 5 1 2
  // index:  0 1 2 3
  //
  // check range
  //if (x == INT_MIN)
  //  return std::string("-2147483648");
  string val;
  int digit_pos = 0;

  if (x<0) {
    val.append("-");
    digit_pos = 1;
  }
  // abs(INT_MIN) is not defined. move it to %10 stage so the range is always with INT_MIN, INT_MIN
  //x = abs(x);
  do {
    val.insert(val.end(),abs(x%10) + '0');
    x = x/10;
  }while(x);

  // reverse from digit_pos to the end the stream
  //for (int i = digit_pos; i <=(digit_pos+val.length()-1)/2; i++)
  //	std::swap(val[i],val[val.length()-1-i+digit_pos]);
  std::reverse(val.begin()+digit_pos, val.end());

  return val;
}

int StringToInt(const string& s) {
  // Implement this placeholder.
  // string: - 5 1 2
  // index:  0 1 2 3
  // number: -512
  // assume no illegal char in the stream
  if  (!s.compare(string("-2147483648")))
    return INT_MIN;

  int sign_pos = s.find_first_of('-');
  int x = 0;
  int digits_pos = 0;

  if (sign_pos  >=0)
     digits_pos = sign_pos+1;
  else
      digits_pos = 0;
  for (int i = digits_pos; i < s.length();i++) {
     x = x*10+s[i]-'0';
  }
  //  INT_MIN * (-1) will still be INT_MIN! because its bits are already overflowing.
  if (sign_pos>=0)
    x *= (-1);
  return x ;
}

void Wrapper(int x, const string& s) {
  if (IntToString(x) != s) {
    throw TestFailureException("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailureException("String to int conversion failed");
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"x", "s"};
  generic_test_main(argc, argv, param_names,
                    "string_integer_interconversion.tsv", &Wrapper);
  return 0;
}
