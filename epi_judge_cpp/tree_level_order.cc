#include <memory>
#include <vector>
#include <queue>

#include "binary_tree_node.h"

using std::unique_ptr;
using std::vector;

//the challenge is to find the most right nodes for a given layer
vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  // Implement this placeholder.
	if (tree.get()== nullptr)
		return {};

	vector<vector<int>> vals;
	vector<int> val;
	std::queue<BinaryTreeNode<int> *> curr_depth_nodes;
	std::queue<BinaryTreeNode<int> *> next_depth_nodes;
	curr_depth_nodes.emplace(tree.get());

	while(!curr_depth_nodes.empty()) {
		BinaryTreeNode<int> *p = curr_depth_nodes.front();

		if (p->left) {
			next_depth_nodes.emplace (p->left.get());
		}
		if (p->right) {
			next_depth_nodes.emplace(p->right.get());
		}
		val.push_back(p->data);
		curr_depth_nodes.pop();
		if (curr_depth_nodes.empty()) {
			curr_depth_nodes = next_depth_nodes;
			vals.push_back(val);
			val.clear();
			next_depth_nodes = {};
		}

	}

  return vals;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree"};
  generic_test_main(argc, argv, param_names, "tree_level_order.tsv",
                    &BinaryTreeDepthOrder);
  return 0;
}
