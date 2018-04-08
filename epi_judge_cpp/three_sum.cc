#include <vector>
#include <algorithm>

using std::sort;
using std::vector;


bool HasTwoSum(vector<int>A, int sum, int start) {
    int left = start;
    int right = A.size()-1;
    while(left <=right) {
        if (A[left] + A[right] > sum)
            right--;
        else if (A[left] + A[right] == sum)
            return true;
        else {
            left ++;
        }
    }
    return false;
}

// O(n^2) complexity
// the problem doesn't need to be distinct index
// otherwise I think a[i] need to be less a[i] <=t/3
// a[i] <= a[j] <= a[k]  a[i]+ a[j] + a[k] = t
bool HasThreeSum(vector<int> A, int t) {
    if (A.size() <1)
        return false;
    
    sort(A.begin(), A.end());
    
    int i =0;
    while(i < A.size()){
        if (HasTwoSum(A, t-A[i],0))
            return true;
        i++;
    }
  return false;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A", "t"};
  generic_test_main(argc, argv, param_names, "three_sum.tsv", &HasThreeSum);
  return 0;
}
