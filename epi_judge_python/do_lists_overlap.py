from is_list_cyclic import has_cycle
from do_terminated_lists_overlap import overlapping_no_cycle_lists
from test_framework.test_failure_exception import TestFailureException
from test_framework.test_utils import enable_timer_hook


def overlapping_lists(l0, l1):
    # Implement this placeholder.
    return None


@enable_timer_hook
def overlapping_lists_wrapper(timer, l0, l1, common, cycle0, cycle1):
    if common:
        if not l0:
            l0 = common
        else:
            it = l0
            while it.next:
                it = it.next
            it.next = common

        if not l1:
            l1 = common
        else:
            it = l1
            while it.next:
                it = it.next
            it.next = common

    if cycle0 != -1 and l0:
        last = l0
        while last.next:
            last = last.next
        it = l0
        for _ in range(cycle0):
            if not it:
                raise RuntimeError('Invalid input data')
            it = it.next
        last.next = it

    if cycle1 != -1 and l1:
        last = l1
        while last.next:
            last = last.next
        it = l1
        for _ in range(cycle1):
            if not it:
                raise RuntimeError('Invalid input data')
            it = it.next
        last.next = it

    common_nodes = set()
    it = common
    while it and id(it) not in common_nodes:
        common_nodes.add(id(it))
        it = it.next

    timer.start()
    result = overlapping_lists(l0, l1)
    timer.stop()

    if not (id(result) in common_nodes or (not common_nodes and not result)):
        raise TestFailureException('Invalid result')


from test_framework import test_utils_generic_main, test_utils

if __name__ == '__main__':
    test_utils_generic_main.generic_test_main('do_lists_overlap.tsv',
                                              overlapping_lists_wrapper)
