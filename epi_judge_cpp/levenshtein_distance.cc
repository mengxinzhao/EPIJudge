#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

// editting distance from A to B
int editDistance(const string &A, int i, const string &B, int j) {
    if( i == 0 )
        return j; // all insertion
    
    if (j == 0)
        return i; // all deletion
    
    if (A[i-1] == B[j-1])
        return editDistance(A, i-1,B,j-1);
    
    //consider all possible solutions
    return 1+ std::min(std::min(editDistance(A,i-1,B,j),  //A[i] deleted
                       editDistance(A,i, B, j-1)),      // B[i] deleted
                       editDistance(A,i-1, B, j-1));  //change
}
int LevenshteinDistance(const string& A, const string& B) {
  

    return  editDistance(A,A.length(), B, B.length());
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A", "B"};
  generic_test_main(argc, argv, param_names, "levenshtein_distance.tsv",
                    &LevenshteinDistance);
  return 0;
}
