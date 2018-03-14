#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>

using std::string;
using std::vector;
using std::pair;
using std::map;

// O(N*M) complexity N= A_size M = B_size
// O(N*M) space
int LevenshteinDistance(const string& A, const string& B) {
    // cache i,j, edit distance. needs to consider empty string.
    vector<vector<int>>tbl(A.length()+1,vector<int>(B.length()+1,0));
    
    for (int i = 0; i <=A.length(); i++)
        for (int j =0; j <=B.length(); j++) {
            if (i==0)
                tbl[i][j] = j ; // all insertion
            else if (j==0)
                tbl[i][j] = i ; // all deletion
            else if (A[i-1] == B[j-1])
                tbl[i][j] = tbl[i-1][j-1];
            else {
                tbl[i][j]  = 1 + std::min(std::min(tbl[i-1][j],tbl[i][j-1]),tbl[i-1][j-1]  );
            }
        }
    return tbl[A.length()][B.length()];
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A", "B"};
  generic_test_main(argc, argv, param_names, "levenshtein_distance.tsv",
                    &LevenshteinDistance);
  return 0;
}
