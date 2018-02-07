#include <memory>
#include <vector>
#include <stack>
#include <set>
#include "bst_node.h"

#include <iostream>
using std::unique_ptr;
using std::vector;

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  // Implement this placeholder.
	std::stack<BSTNode<int> *> path;
	BSTNode<int> * p = tree.get();
	//BSTNode<int> * ret_from_right;
	std::set<BSTNode<int> *> seen;
	vector<int> val;

	// don't bother
	if (p == nullptr)
		return {};

	// visit right ->root->left till number reaches k
	path.push(p);
	while(!path.empty() && val.size() < k) {
		p = path.top();
		while(p->right.get() && seen.find( p->right.get())==seen.end() ) {
			path.push(p->right.get());
			p = p->right.get();
		}
		//visit
		p = path.top();
		seen.insert(p);
		//std::cout<<" " << p->data;
		val.push_back(p->data);
		path.pop();
		//check left
		if (p->left.get()){
			path.push(p->left.get());
		}
	}
	//std::cout<<std::endl;
  return val;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree", "k"};
  generic_test_main(argc, argv, param_names, "k_largest_values_in_bst.tsv",
                    &FindKLargestInBST, &UnorderedComparator<std::vector<int>>);
  return 0;
}
