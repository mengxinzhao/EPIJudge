#include <memory>

#include "bst_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/test_timer.h"

using std::unique_ptr;

bool PairIncludesAncestorAndDescendantOfM(
    const unique_ptr<BstNode<int>>& possible_anc_or_desc_0, //A
    const unique_ptr<BstNode<int>>& possible_anc_or_desc_1, // B
    const unique_ptr<BstNode<int>>& middle) {
    
    auto *p = possible_anc_or_desc_0.get();
    auto *q = possible_anc_or_desc_1.get();
    // after this loop, if middle is not between A,B, one of p,q will be at lower node of A,B
    // if middle is between A,B one of q,p will be pointing to middle
    while (p!= possible_anc_or_desc_1.get() && p!= middle.get()&& q!= possible_anc_or_desc_0.get() && q!= middle.get() && (p || q)) {
        if (p) {
            p = p->data > middle->data?  p->left.get(): p->right.get();
        }
        if (q) {
            q = q->data > middle->data ? q->left.get(): q->right.get();
        }
    }
    //
    if ((p != middle.get() && q != middle.get()) ||
        p == possible_anc_or_desc_1.get() ||
        q == possible_anc_or_desc_0.get()) {
        return false;
    }
    
    if (p == middle.get()){ // p started from A
        //use p to find B
        while (p) {
            if (p->data > possible_anc_or_desc_1->data)
                p = p->left.get();
            else if (p->data == possible_anc_or_desc_1->data)
                return true;
            else
                p = p->right.get();
        }
    }else if (q == middle.get()) { // q started from B
        // use q to find A
        while (q) {
            if (q->data > possible_anc_or_desc_0->data)
                q = q->left.get();
            else if (q->data == possible_anc_or_desc_0->data)
                return true;
            else
                q = q->right.get();
        }
    }
    return false;
}

bool PairIncludesAncestorAndDescendantOfMWrapper(
    TestTimer& timer, const unique_ptr<BstNode<int>>& tree,
    int possible_anc_or_desc_0, int possible_anc_or_desc_1, int middle) {
  auto& candidate0 = MustFindNode(tree, possible_anc_or_desc_0);
  auto& candidate1 = MustFindNode(tree, possible_anc_or_desc_1);
  auto& middle_node = MustFindNode(tree, middle);
  timer.Start();
  bool result =
      PairIncludesAncestorAndDescendantOfM(candidate0, candidate1, middle_node);
  timer.Stop();
  return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "tree",
                                       "possible_anc_or_desc_0",
                                       "possible_anc_or_desc_1", "middle"};
  generic_test_main(argc, argv, param_names,
                    "descendant_and_ancestor_in_bst.tsv",
                    &PairIncludesAncestorAndDescendantOfMWrapper);
  return 0;
}
