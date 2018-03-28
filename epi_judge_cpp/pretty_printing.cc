#include <string>
#include <vector>
#include <climits>
#include <iostream>
using std::string;
using std::vector;
using std::min;

// solve referring to MIT open course algorithm lecture 20
// messiness(i,j) = (line_length- word_length(i,j-1))^2, i current word starting this line, j word begin in the next line
// M[i]= min(mesiness(i,j) + M[j] for j = i+1,...n) i,j word index
// M[i]= INT_MAX if there is split of one word between lines
// M[n] = 0
// result = M[0]
int messiness(const vector<string>& words, int i, int j, int line_length) {
    // total_length = word space + white space
    int k=i;
    int total_length = 0;
    while (k<j-1)
        total_length += words[k++].length() + 1;
    total_length += words[k].length();
    if (total_length > line_length) {
        //std::cout<<i<<", "<<j<<" " << "total_length:"<<total_length<<std::endl;
        return INT_MAX;
    }
    else
        return (line_length - total_length) * (line_length - total_length);
}

// bottom up
// M[n] = 0
// M[n-1]= argmin(messiness(n-1,n) + M[n])
// ...
// M[n-k] = argmin(messiness(n-k,j) + M[j]) j = n-k+1...n-1
int MinimumMessiness(const vector<string>& words, int line_length) {
    vector<int> M(words.size()+1,INT_MAX);
    M[words.size()] = 0;
    for (int i = words.size()-1; i>=0;i--) {
        for (int j = i+1; j<=words.size();j++) {
            int mess_score = messiness(words,i,j, line_length);
            if (mess_score < INT_MAX) {
               M[i] = min((mess_score+M[j]),M[i] );
               //std::cout<<i<<", "<<j<<" " << M[i]<<std::endl;
            }
        }
    }

    
    return M[0];
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"words", "line_length"};
  generic_test_main(argc, argv, param_names, "pretty_printing.tsv",
                    &MinimumMessiness);
  return 0;
}
