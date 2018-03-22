#include "binary_tree_node.h"
#include <iostream>

// recursively add up the all node
int SumRootToLeafHelper(const unique_ptr<BinaryTreeNode<int>> & node, int curr_sum) {
    if (node==nullptr) {
        return curr_sum;
    }
    else {
        curr_sum = curr_sum*2 + node->data;
        if (node->left && node->right)
            return SumRootToLeafHelper(node->left,curr_sum) + SumRootToLeafHelper(node->right,curr_sum);
        else if (node->left && ! node->right)
            return SumRootToLeafHelper(node->left,curr_sum);
        else if (!node->left && node->right)
            return SumRootToLeafHelper(node->right,curr_sum);
        else return curr_sum;
    }
}

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
    int sum = SumRootToLeafHelper(tree,0);
    return sum;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree"};
  generic_test_main(argc, argv, param_names, "sum_root_to_leaf.tsv",
                    &SumRootToLeaf);
  return 0;
}
