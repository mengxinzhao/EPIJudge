from test_framework.test_failure_exception import TestFailureException
from posting_list_node import PostingListNode
from test_framework.test_utils import enable_timer_hook


def copy_postings_list(L):
    # Implement this placeholder.
    return None


def create_posting_list(serialized):
    key_mapping = dict()
    head = None
    for (order, _) in reversed(serialized):
        head = PostingListNode(order, head)
        key_mapping[order] = head

    list_it = head
    for (_, jump_index) in serialized:
        if jump_index != -1:
            list_it.jump = key_mapping.get(jump_index, None)
            if not list_it.jump:
                raise RuntimeError('Jump index out of range')

    return head


def assert_lists_equal(orig, copy):
    node_mapping = dict()
    o_it = orig
    c_it = copy
    while o_it:
        if not c_it:
            raise TestFailureException(
                'Copied list has fewer nodes than the original')
        if o_it.order != c_it.order:
            raise TestFailureException('Order value mismatch')
        node_mapping[o_it] = c_it
        o_it = o_it.next
        c_it = c_it.next

    if c_it:
        raise TestFailureException(
            'Copied list has more nodes than the original')

    o_it = orig
    c_it = copy
    while o_it:
        if c_it in node_mapping:
            raise TestFailureException(
                'Copied list contains a node from the original list')
        if o_it.jump is None:
            if c_it.jump is not None:
                raise TestFailureException(
                    'Jump link points to a different nodes in the copied list')
        else:
            if not node_mapping[o_it.jump] is c_it.jump:
                raise TestFailureException(
                    'Jump link points to a different nodes in the copied list')
        o_it = o_it.next
        c_it = c_it.next


@enable_timer_hook
def copy_postings_list_wrapper(timer, serialized):
    head = create_posting_list(serialized)

    timer.start()
    copy = copy_postings_list(head)
    timer.stop()

    assert_lists_equal(head, copy)


from test_framework import test_utils_generic_main, test_utils

if __name__ == '__main__':
    test_utils_generic_main.generic_test_main('copy_posting_list.tsv',
                                              copy_postings_list_wrapper)
