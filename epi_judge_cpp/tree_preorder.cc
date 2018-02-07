#include <vector>
#include <stack>

#include "binary_tree_node.h"

using std::vector;

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // Implement this placeholder.
	// visit root -> left ->right
	vector<int> val;
	BinaryTreeNode<int> * p = tree.get();
	std::stack<BinaryTreeNode<int> *> path;
	// sanity check
	if (p == nullptr)
		return {};

	path.push(p);
	while(!path.empty()) {
		p = path.top();
		path.pop();
		//visit
		val.push_back(p->data);
		// push right
		if (p->right.get())
			path.push(p->right.get());
		// push left
		if (p->left.get())
			path.push(p->left.get());
	}
	return val;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree"};
  generic_test_main(argc, argv, param_names, "tree_preorder.tsv",
                    &PreorderTraversal);
  return 0;
}
