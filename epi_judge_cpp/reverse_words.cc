#include <string>
#include <algorithm>
#include <iostream>

#include "test_framework/test_timer.h"

using std::string;

void ReverseWords(string* s) {
  // Implement this placeholder.

  // 1st pass reverse the whole string
  int length = s->length();
  for (int idx=0; idx < length/2;idx++)
    std::swap((*s)[idx],(*s)[length-idx-1]);
  //std::cout<<*s<<std::endl;

  // 2nd pass reverse each word
  for (int i =0; i < length;) {
    int start = i;
    int pos = (string(*s,i,length-i)).find_first_of(' ');
    if (pos < 0 ) // reach to the end
        pos = length - i;
    //swap word in pos from start to end
    for (int j=0; j < pos/2;j++)
      std::swap((*s)[start+j],(*s)[start+pos-j-1]);
      //move idx to the begining of another word
    i = start+pos+1;
  }
  return;
}

string ReverseWordsWrapper(TestTimer& timer, string s) {
  string s_copy = s;
  timer.Start();
  ReverseWords(&s_copy);
  timer.Stop();
  return s_copy;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "s"};
  generic_test_main(argc, argv, param_names, "reverse_words.tsv",
                    &ReverseWordsWrapper);
  return 0;
}
