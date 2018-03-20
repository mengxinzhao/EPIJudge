#include <memory>

#include "list_node.h"
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::shared_ptr;

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
				shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
	// sanity check
	if (l0 == nullptr || l1 == nullptr)
		return nullptr;

	// if they the are same anyway
	if (l0 == l1)
		return l1;

	shared_ptr<ListNode<int>> p0 = l0;
	shared_ptr<ListNode<int>> p1 = l1;
	int len_l0 = 0;
	int len_l1 = 0;

	while (p0) {
		p0 = p0->next;
		len_l0++;
	}

	while (p1) {
		p1 = p1 ->next;
		len_l1++;
	}

	shared_ptr<ListNode<int>> LL = (len_l0 > len_l1)? l0:l1;
	// move the diff on the longer
	int i = 0;
	p0 = LL;
	while (i<abs(len_l0 - len_l1)){
		p0 = p0->next;
		i++;
	}
	p1 = (l0==LL)? l1:l0;
	while (p0 && p1 && p0!=p1){
		p0 = p0->next;
		p1 = p1->next;
	}
	return p0;
}

void OverlappingNoCycleListsWrapper(TestTimer& timer,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
	if (common) {
		if (l0) {
			auto i = l0;
			while (i->next) {
				i = i->next;
			}
			i->next = common;
		} else {
			l0 = common;
		}

		if (l1) {
			auto i = l1;
			while (i->next) {
				i = i->next;
			}
			i->next = common;
		} else {
			l1 = common;
		}
	}

	timer.Start();
	auto result = OverlappingNoCycleLists(l0, l1);
	timer.Stop();

	if (result != common) {
		throw TestFailureException("Invalid result");
	}
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
	std::vector<std::string> param_names{"timer", "l0", "l1", "common"};
	generic_test_main(argc, argv, param_names, "do_terminated_lists_overlap.tsv",
	                  &OverlappingNoCycleListsWrapper);
	return 0;
}
