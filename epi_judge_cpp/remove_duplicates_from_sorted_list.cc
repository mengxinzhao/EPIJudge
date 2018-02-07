#include <memory>

#include "list_node.h"

using std::shared_ptr;

shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>>& L) {
  // Implement this placeholder.
	if (L == nullptr)
		return nullptr;

	shared_ptr<ListNode<int>> p = L, next = p->next, tmp = nullptr;

	while (next) {
		if (p->data == next->data ){
			// remove the next one
			p->next = next->next;
			tmp = next;
			next = next->next;
			tmp.reset();
		}else {
			p = next;
			next = p->next;
		}
	}
  return L;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "remove_duplicates_from_sorted_list.tsv",
                    &RemoveDuplicates);
  return 0;
}
