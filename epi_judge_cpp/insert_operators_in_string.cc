#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;

// DP[i,j] denotes target i can be reached by using up to [0,jth] digit.With j+1th digit, possible numbers are
// DP[n,i] * 10 + digits[j+1] or DP[n,i] + digits[j+1] or  DP[n,i] * digits[j+1]
// base case
// DP[i,0] = true if digits[0] == i else false

//
bool ExpressionSynthesisHelper(const vector<int> & digits, int i, int target,unordered_map<int, int> &cache) {
    if (i==0 ) {
        if (target == digits[0])
            return true;
        else
            return false;
    }
    if (cache.find(target) != cache.end())
        return false;
    
    // try all possible candidates
    vector <int> new_targets = {target - digits[i], (target - digits[i])/10, target / digits[i]};
    for (auto candidate: new_targets ) {
        if (ExpressionSynthesisHelper(digits, i-1, candidate,cache) == true)
            return true;
    }
    // cache unsuccessful candidate
    cache[target] = i;
    return false;
}

bool ExpressionSynthesis(const vector<int>& digits, int target) {
    unordered_map<int, int> cache;// to cache  unsuccessful try when a target k can't archieved by using up to ith digits
    return ExpressionSynthesisHelper(digits, digits.size()-1, target,cache);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"digits", "target"};
  generic_test_main(argc, argv, param_names, "insert_operators_in_string.tsv",
                    &ExpressionSynthesis);
  return 0;
}
