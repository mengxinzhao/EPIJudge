#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"

BinaryTreeNode<int>* FindSuccessor(
    const unique_ptr<BinaryTreeNode<int>>& node) {
  // Implement this placeholder.
	// if it has right tree, its successor is the furthest node on the left branch
	// if not its successor is its parent node which has value bigger > node along the in BST
	// or its p->parent->right != p

	BinaryTreeNode<int> *p= node.get();
	if (p->right.get()) {
		p = p->right.get();
		while(p->left.get())
			p = p->left.get();
		return p;
	}else {
		// go back
		while(p->parent && p->parent->right.get() == p) {
			p = p->parent;
		}
		return p->parent;
	}

  return nullptr;
}

int FindSuccessorWrapper(const unique_ptr<BinaryTreeNode<int>>& tree,
                         int node_idx) {
  auto result = FindSuccessor(MustFindNode(tree, node_idx));
  return result ? result->data : -1;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree", "node_idx"};
  generic_test_main(argc, argv, param_names, "successor_in_tree.tsv",
                    &FindSuccessorWrapper);
  return 0;
}
