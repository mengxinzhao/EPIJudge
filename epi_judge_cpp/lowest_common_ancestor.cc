#include <memory>
#include <stack>
#include <algorithm>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::unique_ptr;

BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& tree,
                         const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  // Implement this placeholder.
	// post order travel. keep the root stack from node 0 and node 1
	// the first node kept in the stack is the common ancester

	BinaryTreeNode<int> * p = tree.get();
	std::stack<BinaryTreeNode<int> *> path;
	std::set<BinaryTreeNode<int> *> seen;
	std::stack<BinaryTreeNode<int> *> ca0, ca1; // common ancester path


	if (p == nullptr)
		return {};

	path.push(p);
	while(!path.empty()) {
		p = path.top();
		while (p->left.get() && seen.find(p->left.get())==seen.end()) {
			path.push(p->left.get());
			p = p->left.get();
		}
		// keep the right tree path
		if (p->right.get() && seen.find(p->right.get())==seen.end()) {
			path.push(p->right.get());
			p = p->right.get();
		}  else {
			// visit the node
			p = path.top();
			seen.insert(p);
			//std::cout << "visit " << p->data << std::endl;
			if (p == node0.get())
				ca0 = path;
			if (p == node1.get())
				ca1 = path;
			// seen both
			if (seen.find(node0.get())!= seen.end() && seen.find(node1.get())!= seen.end()) {
				break;
			}
			// pop the path after the node is identified . ca stack  includes the node itself
			// for the reason that that one node could be the ancestor of another one
			path.pop();

		}

	}
	seen.clear();

	int size0= ca0.size();
	int size1 = ca1.size();
	if (size0>size1) {
			while(ca0.size()>ca1.size())
				ca0.pop();
	}
	else {
		while(ca1.size()>ca0.size())
			ca1.pop();
	}
	// the first common one
	while (!ca1.empty() && !ca0.empty()) {
		if (ca0.top() == ca1.top())
			break;
	else {
			ca0.pop();
			ca1.pop();
		}
	}
	return ca0.top();

}

int LcaWrapper(TestTimer& timer, const unique_ptr<BinaryTreeNode<int>>& tree,
               int node0, int node1) {
  timer.Start();
  auto result = LCA(tree, MustFindNode(tree, node0), MustFindNode(tree, node1));
  timer.Stop();

  if (!result) {
    throw TestFailureException("Result can not be nullptr");
  }
  return result->data;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "tree", "node0", "node1"};
  generic_test_main(argc, argv, param_names, "lowest_common_ancestor.tsv",
                    &LcaWrapper);
  return 0;
}
