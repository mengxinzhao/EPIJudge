#include <memory>

#include "list_node.h"
#include "test_framework/test_timer.h"

using std::shared_ptr;

// Delete the node past this one. Assume node is not a tail.
void DeleteAfter(const shared_ptr<ListNode<int>>& node) {
  // Implement this placeholder.
  if (node->next == nullptr)
    return;
  shared_ptr<ListNode<int>> to_delete = node->next;
  node->next = to_delete->next;
  to_delete.reset();
  return;
}

shared_ptr<ListNode<int>> DeleteFromListWrapper(
    TestTimer& timer, const shared_ptr<ListNode<int>>& head, int i) {
  static int nr = 1;
  nr++;
  shared_ptr<ListNode<int>> selected_node = head;
  shared_ptr<ListNode<int>> prev;
  while (i-- > 0) {
    if (!selected_node || !selected_node->next)
      throw std::runtime_error("Node index is out of range");
    prev = selected_node;
    selected_node = selected_node->next;
  }
  timer.Start();
  DeleteAfter(prev);
  timer.Stop();
  return head;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "delete_from_list.tsv", &DeleteFromListWrapper);
  return 0;
}
