#include <memory>
#include <stdlib.h>

#include "binary_tree_node.h"

using std::unique_ptr;

// partition the tree space
bool _IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& node, int left, int right) {
	// assume there is no duplicated value
	if (node == nullptr)
		return true;

	if (node->data < left || node->data > right)
		return false;

	return _IsBinaryTreeBST(node->left,left, node->data) &&
		   _IsBinaryTreeBST(node->right,node->data, right);
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // left node  < root < right node
	return _IsBinaryTreeBST(tree,INT_MIN,INT_MAX);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree"};
  generic_test_main(argc, argv, param_names, "is_tree_a_bst.tsv",
                    &IsBinaryTreeBST);
  return 0;
}
