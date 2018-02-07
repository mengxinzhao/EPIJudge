
#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

#include <stack>
BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node_0,
                         const unique_ptr<BinaryTreeNode<int>>& node_1) {
  // Implement this placeholder.
	// track back from parents pointer to the root.the fist common node from the top is common ancester
	std::stack< BinaryTreeNode<int> *> path0, path1;
	BinaryTreeNode<int> * p = node_0.get();
	while (p) {
		path0.push(p);
		p = p->parent;
	}
	p = node_1.get();
	while (p) {
		path1.push(p);
		p = p->parent;
	}
	//the first common ancester
	while(!path0.empty() && !path1.empty()) {
		if (path0.top()!=path1.top())
			return p;
		else
			p = path0.top();
		path0.pop();
		path1.pop();
	}

  return p;
}

int LcaWrapper(TestTimer& timer, const unique_ptr<BinaryTreeNode<int>>& root,
               int key1, int key2) {
  auto& node1 = MustFindNode(root, key1);
  auto& node2 = MustFindNode(root, key2);

  timer.Start();
  auto result = LCA(node1, node2);
  timer.Stop();

  if (!result) {
    throw TestFailureException("Result can not be nullptr");
  }
  return result->data;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "lowest_common_ancestor.tsv", &LcaWrapper);
  return 0;
}
