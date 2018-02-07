#include "list_node.h"

shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  // Implement this placeholder.
  shared_ptr<ListNode<int>> newList = shared_ptr<ListNode<int>>(new ListNode<int>(-1)), head = newList; // empty head will be removed at the head
  shared_ptr<ListNode<int>> p1 = L1;
  shared_ptr<ListNode<int>> p2 = L2;
	//  make the head first
  while (p1 && p2) {
    if (p1->data <= p2->data) {
	    newList->next = p1;
	    p1 = p1->next;
    }
	  else {
	    newList->next = p2;
	    p2 = p2->next;
    }
	  newList = newList->next;
  }
	if (p1) {
		while (p1) {
			newList->next = p1;
			p1 = p1->next;
			newList = newList->next;
		}
	}
	if (p2) {
		while (p2) {
			newList->next = p2;
			p2 = p2->next;
			newList = newList->next;
		}
	}
	newList = head;
	head = head->next;
	newList.reset();
  return head;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "sorted_lists_merge.tsv", &MergeTwoSortedLists);
  return 0;
}
