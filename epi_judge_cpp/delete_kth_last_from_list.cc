#include <memory>

#include "list_node.h"

using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
	// Implement this placeholder.
	shared_ptr<ListNode<int> > p = L;
	shared_ptr<ListNode<int> > q;

	int N = 0;

	if (k <= 0)
		return nullptr;

	// find the original tail
	while (p) {
		q = p;
		p = p->next;
		N++;
	}

	// start from the begining, stop at  N-k-1
	p = L;
	for (int i =0 ; i<= N-k-1;i++) {
		q = p;
		p = p->next;
	}
	if (p == L) {//delete the head
		 q = p->next;
		 p.reset();
		 return q;
	}else {
		// remove p
		q->next = p->next;
		p.reset();
	}
  return L;
}

// does k start from 0 or 1?
// have to assume k is a valid number
shared_ptr<ListNode<int>> RemoveKthLast2(const shared_ptr<ListNode<int>>& L,
                                        int k) {
	// Implement this placeholder.
	shared_ptr<ListNode<int> > p = L;
	shared_ptr<ListNode<int> > prev;
	shared_ptr<ListNode<int> > ref = L;

	// handle head
	if (p->next == nullptr && k==1){
		p.reset();
		return nullptr;
	}
	// move ref head k-1 node ahead of real list
	for (int i =0; i<k; i++) {
		p = p->next;
	}
	ref = p;
	p = L;

	while(ref) {
		ref = ref->next;
		prev = p;
		p= p->next;
	}

	// ref reaches to the end p points to the node to be deleted. prev points its previous node.
	if (prev) {
		prev->next = p->next;
		p.reset();
	}else {
		// head node is deleted
		prev = L;
		p = L->next;
		prev.reset();
		return p;
	}

	return L;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"L", "k"};
  generic_test_main(argc, argv, param_names, "delete_kth_last_from_list.tsv",
                    &RemoveKthLast);
  return 0;
}
