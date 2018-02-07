#include <stdlib.h>
#include "binary_tree_node.h"

int height(const unique_ptr<BinaryTreeNode<int> > &root) {
	if (root  == nullptr)
		return  0;
	else
		return std::max(height(root->left),height(root->right)) +1;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
	// Implement this placeholder.
	// balanced as  abs(height(tree->left) - height(tree->right))<=1
	// for all nodes
	if (tree == nullptr)
		return true;
	unique_ptr<BinaryTreeNode<int>> &left = tree->left;
	unique_ptr<BinaryTreeNode<int>> &right = tree->right;
	if (left && right == nullptr)
		return (height(left) <= 1);
	else if (left== nullptr && right)
		return (height(right) <= 1);
	else
		return IsBalanced(left) && IsBalanced(right);

}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree"};
  generic_test_main(argc, argv, param_names, "is_tree_balanced.tsv",
                    &IsBalanced);
  return 0;
}
