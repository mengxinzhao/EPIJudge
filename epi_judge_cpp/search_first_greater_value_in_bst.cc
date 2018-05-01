#include <memory>

#include "bst_node.h"
#include <set>
#include <iostream>
#include <stack>

using std::unique_ptr;
using std::stack;

// when k's found, and it has a right branch, the result is the leftest child on its right branch
// if it doesn't have right branch, the result is the k first parent nodes > k.
// that is the first parent node that is taking the left turn to find k

// when k is not in BST tree, when iterating to the end leave j
// if k < j, j is the result (that means if k exist k is the j's left child
// if k > j , the 1st parent along the path > k is result
BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree,
                                    int k) {

	BstNode<int> * p = tree.get(); // travelling node
	BstNode<int> * q = nullptr;
    stack<BstNode<int> *> parents; // tracking parents node that is making left turn
	while(p) {
        //std::cout<<"checking "<<p->data<<std::endl;
		if (p->data > k) {
            parents.push(p);
            p = p->left.get();
		}else if (p->data == k) {
            q = p->right.get(); //it's right child;
			break;
        }else if (p->data<k) {
			p = p->right.get();
        }
	}
    
    if (!p ) {// not in BST
        if (parents.size()>0) {
            if ( k < parents.top()->data ) {
                return parents.top();
            }
           else {
               while(parents.top()->data < k) {
                   parents.pop();
               }
               return parents.top();
           }
        }else // a null root
            return nullptr;
    } else { // in BST
        if (q == nullptr) {// no right child
            if (!parents.empty()){
                while(parents.top()->data < k) {
                    parents.pop();
                }
                return parents.top();
            }else
                return nullptr;
        }
        else { // has right child
            while(q->left )
                q = q->left.get();
            return q;
        }
    }
    
}




int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"tree", "k"};
  generic_test_main(argc, argv, param_names,
                    "search_first_greater_value_in_bst.tsv",
                    &FindFirstGreaterThanKWrapper);
  return 0;
}
