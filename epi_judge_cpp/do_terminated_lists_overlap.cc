#include <memory>

#include "list_node.h"
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::shared_ptr;

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> L1, shared_ptr<ListNode<int>> L2) {
	// Implement this placeholder.
	// sanity check
	if (L1 == nullptr || L2 == nullptr)
		return nullptr;

	// if they the are same anyway
	if (L1 == L2)
		return L1;

	shared_ptr<ListNode<int>> p1 = L1;
	shared_ptr<ListNode<int>> p2 = L2;
	int len_L1 = 0;
	int len_L2 = 0;

	while (p1) {
		p1 = p1->next;
		len_L1++;
	}

	while (p2) {
		p2 = p2->next;
		len_L2++;
	}

	shared_ptr<ListNode<int>> LL = (len_L1 > len_L2)? L1:L2;
	// move the diff on the longer
	int i = 0;
	p1 = LL;
	while (i<abs(len_L1 - len_L2)){
		p1 = p1->next;
		i++;
	}
	p2 = (L1==LL)? L2:L1;
	while (p1 && p2 && p1!=p2){
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;

}

void OverlappingNoCycleListsWrapper(TestTimer& timer,
                                    shared_ptr<ListNode<int>> p1,
                                    shared_ptr<ListNode<int>> p2,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (!p1) {
      p1 = common;
    } else {
      auto l1 = p1;
      while (l1->next) {
        l1 = l1->next;
      }
      l1->next = common;
    }

    if (!p2) {
      p2 = common;
    } else {
      auto l2 = p2;
      while (l2->next) {
        l2 = l2->next;
      }
      l2->next = common;
    }
  }

  timer.Start();
  auto result = OverlappingNoCycleLists(p1, p2);
  timer.Stop();

  if (result != common) {
    throw TestFailureException("Invalid result");
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "do_terminated_lists_overlap.tsv",
                    &OverlappingNoCycleListsWrapper);
  return 0;
}
