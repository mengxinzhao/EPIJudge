#include <tuple>
#include <vector>
#include <algorithm>

using std::sort;

#include "test_framework/test_utils_serialization_traits.h"

using std::vector;

struct PairedTasks {
  int task_1, task_2;
    PairedTasks(int _task1, int _task2):task_1(_task1),task_2(_task2) {}
};

// greedy algorithm
// pick two ends for each worker till left right meets each other

vector<PairedTasks> OptimumTaskAssignment(vector<int> task_durations) {
    
    if (task_durations.empty())
        return {};
    sort(task_durations.begin(), task_durations.end());
    vector<PairedTasks> result;
    size_t left = 0;
    size_t right = task_durations.size()-1;
    
    while(left<right) {
        result.emplace_back(task_durations[left],task_durations[right]);
        left++;
        right--;
    }
    return result;
}

template <>
struct SerializationTraits<PairedTasks> : UserSerTraits<PairedTasks, int, int> {
};

bool operator==(const PairedTasks& lhs, const PairedTasks& rhs) {
  return std::tie(lhs.task_1, lhs.task_2) == std::tie(rhs.task_1, rhs.task_2);
}

std::ostream& operator<<(std::ostream& out, const PairedTasks& t) {
  return EpiPrint(out, std::make_tuple(t.task_1, t.task_2));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"task_durations"};
  generic_test_main(argc, argv, param_names, "task_pairing.tsv",
                    &OptimumTaskAssignment);
  return 0;
}
