#include <vector>
#include <algorithm>
using std::vector;
using std::sort;

// waiting time till ith request
// W[i]  =  sum(t[j])  j=0...i-1
// TotalTime = sum(W[i])
// leave the biggest service time item out of the sum equation
int MinimumTotalWaitingTime(vector<int> service_times) {
    
    sort(service_times.begin(), service_times.end());
    int wait_time = 0;
    for (int i=0;i<service_times.size();i++)
        wait_time += service_times[i] *(service_times.size()-(i+1));
    return wait_time;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"service_times"};
  generic_test_main(argc, argv, param_names, "minimum_waiting_time.tsv",
                    &MinimumTotalWaitingTime);
  return 0;
}
