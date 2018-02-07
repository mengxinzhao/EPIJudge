#include <memory>

#include "bst_node.h"
#include <set>
#include <stack>

using std::unique_ptr;
// need to use BST property
BSTNode<int>* FindFirstGreaterThanK(const unique_ptr<BSTNode<int>>& tree,
                                    int k) {
  // Implement this placeholder.
	BSTNode<int> * p = tree.get();
	BSTNode<int> * q = nullptr;
	if (p == nullptr)
		return nullptr;
	// find the first node > k along the path
	while (p && p->data <= k) {
		q = p;
		p = p->right.get();
	}
	// the most right node still less than k. no hope return
	if (p == nullptr)
		return nullptr;
	// the first node > k. the value lies in its left tree
	if (p->left.get() == nullptr)
		return p;
	//left -> node-> right travel the subtree with root p
	//return the first node value > k
	std::stack<BSTNode<int> *>path;
	std::set<BSTNode <int> * >seen;
	path.push(p);
	while(!path.empty()) {
		p = path.top();
		while(p->left.get() && seen.find(p->left.get())==seen.end()) {
			path.push(p->left.get());
			p = p->left.get();
		}
		p = path.top();
		seen.insert(p);
		// visit
		if (p->data > k)
			return p;
		path.pop();

		if (p->right.get()) {
			path.push(p->right.get());
		}

	}

  return nullptr;
}

// need to use BST property
// if key doesn't exist or no key larger than k is present return nullptr
BSTNode<int>* FindFirstGreaterThanK2(const unique_ptr<BSTNode<int>>& tree,
                                    int k) {
	// Implement this placeholder.
	BSTNode<int> * p = tree.get();
	BSTNode<int> * q = nullptr;
	BSTNode<int> *r = nullptr;

	while(p) {
		if (p->data > k) {
			p = p->left.get();
			q = p;
		}else if (p->data == k) {
			r = q;
			q = p->right.get();
			break;
		}else if (p->data<k)
			p = p->right.get();
	}

	if (!p) return nullptr; // key not found
	else if (q) return r; // key found and has right node
	else return q;  // key found but no right node return its ancester that > k
}


int FindFirstGreaterThanKWrapper(const unique_ptr<BSTNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "search_first_greater_value_in_bst.tsv",
                    &FindFirstGreaterThanKWrapper);
  return 0;
}
