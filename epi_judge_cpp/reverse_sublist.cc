#include "list_node.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  // Implement this placeholder.
	// basic sanity check
	if (start < 1 ||  start > finish || L == nullptr )
		return L;

	// no need of reversing
	if (start == finish)
		return L;

	// advance to start point
	int i = 1;
	shared_ptr<ListNode<int>> p = L, prev = nullptr, next = p->next;
	while (i++ < start){
		prev = p;
		p = p->next;
		next = p->next;
	}
	// reverse nodes from start to finish
	// prev, p, next
	i = start;
	shared_ptr<ListNode<int>> pp = prev,start_p = p;
	while (i++ <= finish && p) {
		p->next = pp;
		pp = p;
		p = next;
		if (p)
			next = p->next;
	}
	// pp points to finish point, p and next all after the window
	// hook up the old chain
	// ...prev ->finsih ->....->start->next...
	if (prev)
		prev->next = pp;
	else
		L = pp;
	start_p->next = p;
  return L;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"L", "start", "finish"};
  generic_test_main(argc, argv, param_names, "reverse_sublist.tsv",
                    &ReverseSublist);
  return 0;
}
