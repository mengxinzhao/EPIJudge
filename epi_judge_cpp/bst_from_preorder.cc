#include <memory>

#include "bst_node.h"

using std::unique_ptr;
using std::vector;
using std::make_unique;
// preorder ==> root --> left -->right
//[3, 2, 1, 5, 4, 6]  ["3", "2", "5", "1", "null", "4", "6"]
//
unique_ptr<BstNode<int>> RebuildBSTFromPreorderHelper(const vector<int> & preorder_sequence, int root_idx,int right){
    // build root
    if (root_idx>right)
        return nullptr;
    
    unique_ptr<BstNode<int>> root = make_unique<BstNode<int>>(preorder_sequence[root_idx]);
    int j=root_idx+1;
    // find right node
    while(j <=right) {
        if (preorder_sequence[j] > preorder_sequence[root_idx])
            break;
        j++;
    }
    root->left = RebuildBSTFromPreorderHelper(preorder_sequence, root_idx+1, j-1);
    if (j<=right)
        root->right = RebuildBSTFromPreorderHelper(preorder_sequence, j, right);
    return root;
}

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(
    const vector<int>& preorder_sequence) {
    return RebuildBSTFromPreorderHelper(preorder_sequence,0, preorder_sequence.size()-1);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"preorder_sequence"};
  generic_test_main(argc, argv, param_names, "bst_from_preorder.tsv",
                    &RebuildBSTFromPreorder);
  return 0;
}
