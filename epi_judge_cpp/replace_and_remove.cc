#include <iterator>
#include <string>
#include <vector>

#include "test_framework/test_timer.h"

using std::string;
using std::vector;

void insertA(char *s,int pos);


int ReplaceAndRemove(int size, char s[]) {
  // Implement this placeholder.
  // replace all a with dd and remove b
  // a c b a d e b g e
  // remove b
  int j=0;
  int len  = 0;
  int num_a = 0;
  // remove b
  for (int i=0;i < size; i++) {
    if (s[i] != 'b') {
      s[j] = s[i];
      j++;
      len++;
    }
    if (s[i]=='a')
      num_a++;
  }
  // final length: len + num_a
  j = len+num_a-1;
  for (int i=len-1; i>=0;i--) {
    int k = i;
    while (s[i]!='a') {
      i--;
      if (i <= 0)
  	  break;
    }
    if (s[i] == 'a')  {
      while (k >= i + 1)
        s[j--] = s[k--];
      s[j--] = 'd';
      s[j--] = 'd';
    }
  }
  return len+num_a;
}

vector<string> ReplaceAndRemoveWrapper(TestTimer& timer, int size,
                                       const vector<string>& input_s) {
  std::vector<char> s(input_s.size(), '\0');
  for (int i = 0; i < input_s.size(); ++i) {
    if (!input_s[i].empty()) {
      s[i] = input_s[i][0];
    }
  }

  timer.Start();
  int res_size = ReplaceAndRemove(size, s.data());
  timer.Stop();

  vector<string> result;
  for (int i = 0; i < res_size; ++i) {
    result.emplace_back(string(1, s[i]));
  }
  return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "replace_and_remove.tsv",
                    &ReplaceAndRemoveWrapper);
  return 0;
}
