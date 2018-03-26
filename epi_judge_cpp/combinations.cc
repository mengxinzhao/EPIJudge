#include <vector>
#include <iostream>

using std::vector;

// C(n,i) = C(n-1,i) + C(n-1,i-1)
// 2^(n-k) calls
// O(2^n) complexity
void CombinationsHelper(int n, int k, vector<vector<int>> &result, vector<int> curr, int start) {
    if (curr.size()==k) {
        result.push_back(curr);
        return;
    }
    
    //choose start, select k-1-curr.size() elements from start+1 to the end
    if (k-curr.size() -1 <= n-start -1) {
        curr.push_back(start+1);     // input range [1,...n] val = index+1
        CombinationsHelper(n,k,result,curr, start+1);
        curr.pop_back();
    }
    //do not choose start, select k-curr.size() elements from start+1 to the end
    if (k-curr.size() <= n-start-1) {
        CombinationsHelper(n,k,result,curr, start+1);
    }

}

vector<vector<int>> Combinations(int n, int k) {
    vector<vector<int> > result;
    vector<int> curr;
    CombinationsHelper(n,k,result,curr,0);
    return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"n", "k"};
  generic_test_main(argc, argv, param_names, "combinations.tsv", &Combinations,
                    &UnorderedComparator<std::vector<std::vector<int>>>);
  return 0;
}
