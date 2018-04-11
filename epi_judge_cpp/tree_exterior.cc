#include <vector>
#include <queue>
#include <utility>
#include "binary_tree_node.h"
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::vector;
using std::queue;
using std::move;

// level travel the tree and output the leaf nodes
// insert the last layer
// from N-1 to 2 layer
// insert left to the beginning of the vector, right to the end of the vector
// insert root to the beginning of the vector
//           1
//        /    \
//       2      3
//     /  \    /  \
//    4    5  6    7
//  /   \      \
// 8     9      10
//               \
//                11
// output: 1, 2, 4, 8, 9, 11, 7, 3

// an exterior node is either a leave node or
// when its parent is an exterior node on the left side and the node
//          is its left child/ node is its right child and left child == null
// when its parent is an exterior node on the right side and the node
//          is its right child/node is its left child and right child == null
void GetLeftExterior(const unique_ptr<BinaryTreeNode<int>>& root,
                   vector<const unique_ptr<BinaryTreeNode<int>> *>&result,
                   bool exterior_node)
{
    if (root==nullptr)
        return;
    if (exterior_node || (root->left== nullptr && root->right == nullptr) )
        result.push_back(&root);
    GetLeftExterior(root->left,result,exterior_node);
    GetLeftExterior(root->right,result,exterior_node &&root->left == nullptr );
}

// sequence: visit left, visit right, visit itself
void GetRightExterior(const unique_ptr<BinaryTreeNode<int>>& root,
                     vector<const unique_ptr<BinaryTreeNode<int>> *>&result,
                     bool exterior_node)
{
    if (root==nullptr)
        return;
    GetRightExterior(root->left,result,exterior_node &&root->right == nullptr );
    GetRightExterior(root->right,result,exterior_node);
    if (exterior_node || (root->left== nullptr && root->right == nullptr) )
        result.push_back(&root);
}

vector<const unique_ptr<BinaryTreeNode<int>>*> ExteriorBinaryTree(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
    if (tree == nullptr)
        return {};
    
    vector<const unique_ptr<BinaryTreeNode<int>> *>result;
    result.push_back(&tree);
    GetLeftExterior(tree->left,result,true);
    GetRightExterior(tree->right, result, true);
    
    return result;
}

vector<int> CreateOutputVector(
    const vector<const unique_ptr<BinaryTreeNode<int>>*>& L) {
  if (std::find(std::begin(L), std::end(L), nullptr) != std::end(L)) {
    throw TestFailureException("Resulting list contains nullptr");
  }
  std::vector<int> output;
  for (const auto* l : L) {
    output.push_back((*l)->data);
  }
  return output;
}

vector<int> ExteriorBinaryTreeWrapper(
    TestTimer& timer, const unique_ptr<BinaryTreeNode<int>>& tree) {
  timer.Start();
  auto result = ExteriorBinaryTree(tree);
  timer.Stop();
  return CreateOutputVector(result);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "tree"};
  generic_test_main(argc, argv, param_names, "tree_exterior.tsv",
                    &ExteriorBinaryTreeWrapper);
  return 0;
}
