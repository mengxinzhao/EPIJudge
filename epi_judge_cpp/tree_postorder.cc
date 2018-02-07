#include <memory>
#include <vector>
#include <stack>
#include <set>

#include "binary_tree_node.h"

using std::unique_ptr;
using std::vector;

// We use stack and previous node pointer to simulate postorder traversal.
vector<int> PostorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
	// Implement this placeholder.
	// post order travel.
	BinaryTreeNode<int> * p = tree.get();
	std::stack<BinaryTreeNode<int> *> path;
	std::set<BinaryTreeNode<int> *> seen;
	vector<int> val;

	if (p == nullptr)
		return {};

	path.push(p);
	while(!path.empty()) {
		p = path.top();
		while (p->left.get() && seen.find(p->left.get())==seen.end()) {
			path.push(p->left.get());
			//std::cout<<"push left/root node "<<p->left.get()->data<<std::endl;
			p = p->left.get();
		}
		// visit the right
		if (p->right.get() && seen.find(p->right.get())==seen.end()) {
			//std::cout<<"push right node "<<p->right->data<<std::endl;
			path.push(p->right.get());
			p = p->right.get();
		}  else {
			// visit the node
			p = path.top();
			val.emplace(val.end(), p->data);
			seen.insert(p);
			//std::cout << "visit " << p->data << std::endl;
			path.pop();
		}

	}
	return val;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree"};
  generic_test_main(argc, argv, param_names, "tree_postorder.tsv",
                    &PostorderTraversal);
  return 0;
}
