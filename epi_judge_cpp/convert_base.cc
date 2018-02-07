#include <string>
#include <algorithm>
using std::string;

int  char_to_int(char c) {
    if (c - '0' >=0 && c-'9'<=0)
        return c-'0';
    else if (c-'a' >=0 && c-'f'<=0)
        return c-'a'+10;
    else if (c-'A' >=0 && c-'F'<=0)
        return c-'A'+10;
	//better throw exception here if an invalid char is given
}

char int_to_char(int i) {
    if (i>=0 && i<=9)
        return i+'0';
    else if (i>=10 && i<=15)
        return 'A'+i-10;
}

// N = a0 *base ^0 + a1 * base^1 + a2 * base^2 + ...+an * base^n
// string layout
// byte 0 MSB or sign  ...byte n LSB
//special case 0, -0
string ConvertBase(const string& num_as_string, int b1, int b2) {
  // Implement this placeholder.
    int minus_pos = num_as_string.find_first_of('-');
	int N_as_b1 = 0 ;
	string val("");

	for (int idx = minus_pos+1; idx < num_as_string.length(); idx++)
		N_as_b1 = N_as_b1 * b1 + char_to_int(num_as_string[idx]);

	if (N_as_b1 == 0)
		return num_as_string;

    if (minus_pos>=0)
        val+='-';

    while (N_as_b1) {
		val+=int_to_char(N_as_b1 %b2) ;
		N_as_b1 /= b2;
	}

    if (minus_pos>=0)
    	std::reverse(val.begin()+1,val.end());
    else
        std::reverse(val.begin(),val.end());

      return val;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  generic_test_main(argc, argv, param_names, "convert_base.tsv", &ConvertBase);
  return 0;
}
