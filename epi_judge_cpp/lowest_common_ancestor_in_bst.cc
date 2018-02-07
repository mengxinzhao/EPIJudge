#include <memory>

#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::unique_ptr;

// Input nodes are nonempty and the key at s is less than or equal to that at
// b.
// the easiest way is to search for the two keys
// keep the stack. the last common node is LCA
// this is not O(1) space solution
BSTNode<int>* FindLCA(const unique_ptr<BSTNode<int>>& tree,
                      const unique_ptr<BSTNode<int>>& s,
                      const unique_ptr<BSTNode<int>>& b) {
  // Implement this placeholder.
	BSTNode<int> *p = tree.get();
	while(p) {
		if (p->data > b.get()->data) { // > the bigger one between the two
			p = p->left.get();
		}else if (p->data < s.get()->data) { // < the smaller one between the two
			p = p->right.get();
		}else if ((p->data > s.get()->data && p->data < b.get()->data)
						  ||(p->data == s.get()->data)
		          || (p->data== b.get()->data))
			// can't meet both
			// smaller one gets searched first. bigger node is on its right branch
			// bigger one gets searched first. smaller node is on its left branch
			return p;

	}

  return tree.get();
}

int LcaWrapper(TestTimer& timer, const std::unique_ptr<BSTNode<int>>& root,
               int key1, int key2) {
  auto& node1 = MustFindNode(root, key1);
  auto& node2 = MustFindNode(root, key2);
  timer.Start();
  auto result = FindLCA(root, node1, node2);
  timer.Stop();
  if (!result) {
    throw TestFailureException("Result can not be nullptr");
  }
  return result->data;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "lowest_common_ancestor_in_bst.tsv",
                    &LcaWrapper);
  return 0;
}
