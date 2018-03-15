#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

// O(N+m) complexity
// N size of A, m size of unique element in A
int FindElementAppearsOnce(const vector<int>& A) {
    unordered_map<int, vector<int>> tbl;
    
    for (int i=0; i < A.size();i++) {
        tbl[A[i]].push_back(i);
    }
    
    for (const  auto &iter: tbl ) {
        if (iter.second.size()==1)
            return iter.first;
    }
    return 0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "element_appearing_once.tsv",
                    &FindElementAppearsOnce);
  return 0;
}
