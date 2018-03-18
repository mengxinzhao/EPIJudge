#include <memory>
#include <unordered_set>

using std::unordered_set;

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::unique_ptr;

// track the path in set
// O(d) d: distance from  the deepest node  to the LCA
// worst time and space: O(h) if two nodes are equally deep h: distance from the node to LCA
BinaryTreeNode<int>* LCA(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
    unordered_set<BinaryTreeNode<int> *> tracks;
    BinaryTreeNode<int> * p0 = node0.get();
    BinaryTreeNode<int> * p1 = node1.get();
    while(p0 || p1) {
        if (p0 != nullptr && tracks.find(p0)!=tracks.end())
            return p0;
        else
            tracks.emplace(p0);
        if (p1 != nullptr && tracks.find(p1)!=tracks.end())
            return p1;
        else
            tracks.emplace(p1);
        if (p0!=nullptr)
            p0 = p0->parent;
        if (p1 != nullptr)
            p1 = p1->parent;
        
    }
    return nullptr;
}

int LcaWrapper(TestTimer& timer, const unique_ptr<BinaryTreeNode<int>>& tree,
               int node0, int node1) {
  timer.Start();
  auto result = LCA(MustFindNode(tree, node0), MustFindNode(tree, node1));
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
