#include <memory>
#include <vector>
#include <stack>
#include <set>
#include "binary_tree_node.h"

using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // Implement this placeholder.
	// visit left ->node->right
	vector<int> val;
	BinaryTreeNode<int> * p = tree.get();
	std::stack<BinaryTreeNode<int> *> path;
	std::set<BinaryTreeNode<int> *> seen;

	// sanity check
	if (p == nullptr)
		return {};

	path.push(p);
	while(!path.empty()) {
		p = path.top();
		while(p->left.get() && seen.find(p->left.get())== seen.end()) {
			path.push(p->left.get());
			p = p->left.get();
		}
		//visit
		p = path.top();
		seen.insert(p);
		val.push_back(p->data);
		path.pop();

		// check right
		if (p->right.get()) {
			path.push(p->right.get());
		}

	}
  return val;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "tree_inorder.tsv", &InorderTraversal);
  return 0;
}
