#include <vector>

#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::max;

struct Item {
  int weight, value;
};

// solve referring to MIT algorithm lecture 21.
// DP[i][j]: optimal value of selecting up to ith item under weight j
// DP[i,j] = max(DP[i-1,j], v[i] + DP[i-1, j-w[i]] if  w[i] <j )  i>=1
int OptimumSubjectToCapacity(const vector<Item>& items, int capacity) {
    vector<vector<int>> DP(items.size()+1, vector<int>(capacity+1,0) );
    for (int i=1; i<=items.size();i++) {
        for (int j = 0;j <=capacity;j++){
            if (j-items[i-1].weight >=0)  // item index starts from 0 so i-1s
                DP[i][j] = max(DP[i-1][j], items[i-1].value + DP[i-1][j-items[i-1].weight]);
            else
                DP[i][j] = DP[i-1][j];
        }
    }
    return DP[items.size()][capacity];
}

template <>
struct SerializationTraits<Item> : UserSerTraits<Item, int, int> {};

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"items", "capacity"};
  generic_test_main(argc, argv, param_names, "knapsack.tsv",
                    &OptimumSubjectToCapacity);
  return 0;
}
