#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/test_failure_exception.h"

using std::unique_ptr;
using std::vector;
using std::make_unique;

unique_ptr<BstNode<int>> BuildNode(const vector<int> &A, int left, int right){
    if (left > right)
        return nullptr;
    int mid= left + (right - left)/2;
    auto new_root = make_unique<BstNode<int>>(A[mid]);
    new_root->left = BuildNode(A,left, mid-1);
    new_root->right = BuildNode(A,mid+1, right);
    return new_root;
}

unique_ptr<BstNode<int>> BuildMinHeightBSTFromSortedArray(
    const vector<int>& A) {
    return BuildNode(A,0,A.size()-1);
}

int BuildMinHeightBSTFromSortedArrayWrapper(TestTimer& timer,
                                            const vector<int>& A) {
  timer.Start();
  unique_ptr<BstNode<int>> result = BuildMinHeightBSTFromSortedArray(A);
  timer.Stop();

  if (GenerateInorder(result) != A) {
    throw TestFailureException("Result binay tree mismatches input array");
  }
  return BinaryTreeHeight(result);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "A"};
  generic_test_main(argc, argv, param_names, "bst_from_sorted_array.tsv",
                    &BuildMinHeightBSTFromSortedArrayWrapper);
  return 0;
}
