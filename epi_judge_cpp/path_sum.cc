#include <memory>

#include "binary_tree_node.h"

using std::unique_ptr;

// recursively query each possibility
// pathsum(node, sum ) = node->weight == sum ||  pathsum(node->left, sum-node->weight) == true
//                      ||pathsum(node->right, sum-node->weight) == true
bool HasPathSum(const unique_ptr<BinaryTreeNode<int>>& tree,
                int remaining_weight) {
    if (tree == nullptr) {
        return false;
    }else if (tree ->data == remaining_weight && tree->left == nullptr && tree->right == nullptr) {
        //std::cout<<tree -> data <<std::endl;
        return true;
    }
    else {
       return (HasPathSum(tree->left, remaining_weight-tree->data)
        || HasPathSum(tree->right, remaining_weight-tree->data));
    }
    
}


#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree", "remaining_weight"};
  generic_test_main(argc, argv, param_names, "path_sum.tsv", &HasPathSum);
  return 0;
}
