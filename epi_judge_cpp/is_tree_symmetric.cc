#include "binary_tree_node.h"
#include <vector>

void printLevel(std::vector<BinaryTreeNode<int> *> A) {
	for (int i =0; i< A.size();i++) {
		if (A[i])
			std::cout<<A[i]->data<<" ";
		else
			std::cout<<"null" << " ";
	}
	std::cout<<std::endl;
}

// a level array looks like
// nullptr 1 4 4 1 nullptr
bool IsArraySymmetric(std::vector<BinaryTreeNode<int> *> A) {
	//printLevel(A);
	for (int i =0; i< A.size()/2;i++){
		// both null or both same numbers
		if ((!A[i] && !A[A.size()-1-i]) || (A[i] && A[A.size()-1-i] && A[i]->data==A[A.size()-1-i]->data))
			continue;
		else
			return false;
	}
	return true;
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // Implement this placeholder.
	// level travel the tree
	// for each level the data should be symmetrical
	std::vector<BinaryTreeNode<int> *> curr_level({tree.get()});
	std::vector<BinaryTreeNode<int> *> next_level;

	while(!curr_level.empty()) {
		BinaryTreeNode<int> * curr = curr_level.back();
		if (curr) {
			next_level.emplace(next_level.end(), curr->left.get());
			next_level.emplace(next_level.end(), curr->right.get());
		}
		curr_level.pop_back();
		if (curr_level.empty()) {
			//check if next level is symetrical
			if (!next_level.empty()) {
				if (!IsArraySymmetric(next_level))
					return false;
			}
			curr_level = next_level;
			next_level.clear();
		}

	}
  return true;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree"};
  generic_test_main(argc, argv, param_names, "is_tree_symmetric.tsv",
                    &IsSymmetric);
  return 0;
}
