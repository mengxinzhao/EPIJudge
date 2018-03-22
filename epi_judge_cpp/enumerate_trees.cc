#include <algorithm>
#include <stack>
#include <vector>
#include <iostream>

#include "binary_tree_node.h"
#include "test_framework/test_timer.h"

using std::vector;
using std::make_unique;
// again a catalan number question
// C(0)=1, C(n+1)= sum[ C(i)C(n-i)] from i=0,n n>=0
// recursively allocate i nodes on the left and n-i-1 nodes on the right
vector<unique_ptr<BinaryTreeNode<int>>> GenerateAllBinaryTreesHelper(int start,int end) {
    vector<unique_ptr<BinaryTreeNode<int>>> result;
    if (start >end) {
        result.emplace_back(nullptr);
    }else {
        for (int i=start;i<=end;i++) {
            auto left_trees = GenerateAllBinaryTreesHelper(start,i-1);
            auto right_trees = GenerateAllBinaryTreesHelper(i+1, end);
            for (auto &left_tree: left_trees)
                for (auto &right_tree : right_trees)
                    result.emplace_back(new BinaryTreeNode<int>(i,move(left_tree),move(right_tree)));
        }
    }
    return result;
}


vector<unique_ptr<BinaryTreeNode<int>>> GenerateAllBinaryTrees(int num_nodes) {
  auto result= GenerateAllBinaryTreesHelper(0,num_nodes-1);
    std::cout<<"tree size: "<<result.size()<<std::endl;
    return result;
}

vector<int> SerializeStructure(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> result;

  std::stack<BinaryTreeNode<int>*> stack;
  stack.push(tree.get());
  while (!stack.empty()) {
    auto p = stack.top();
    stack.pop();
    result.push_back(p != nullptr);
    if (p) {
      stack.push(p->left.get());
      stack.push(p->right.get());
    }
  }
  return result;
}

vector<vector<int>> GenerateAllBinaryTreesWrapper(TestTimer& timer,
                                                  int num_nodes) {
  timer.Start();
  auto result = GenerateAllBinaryTrees(num_nodes);
  timer.Stop();

  vector<vector<int>> serialized;
  for (auto& x : result) {
    serialized.push_back(SerializeStructure(x));
  }
  std::sort(begin(serialized), end(serialized));
  return serialized;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "num_nodes"};
  generic_test_main(argc, argv, param_names, "enumerate_trees.tsv",
                    &GenerateAllBinaryTreesWrapper);
  return 0;
}
