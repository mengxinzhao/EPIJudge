#include <array>
#include <vector>
#include <algorithm>
#include <iostream>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::vector;

typedef enum { RED, WHITE, BLUE } Color;

void DutchFlagPartition(int pivot_index, vector<Color>* A_ptr) {
  // Implement this placeholder.
  // better to return error when pivot_index bigger than the length of vector size
  vector<Color> &v = *A_ptr;
  int i = 0,num_of_pivot=0;
  Color pivot = v[pivot_index];
  vector<int> smaller;
  vector<int> bigger;
  while(i <v.size() ) {
    if  (v[i] <v[pivot_index]){
      smaller.push_back(v[i]);
    }else if (v[i]==v[pivot_index]) {
      num_of_pivot++;
    } else {
      bigger.push_back(v[i]);
    }
    i++;
  }
  i=0;
  for (; i< smaller.size();i++ ) {
    v[i] = static_cast<Color>(smaller[i]);
  }
  int j=0;
  for (;j<num_of_pivot;j++ )
    v[j+i] = pivot;
  int k = 0;
  for (; k< bigger.size();k++)
    v[j+i+k]= static_cast<Color>(bigger[k]);

  return;
}

void DutchFlagPartitionWrapper(TestTimer& timer, const vector<int>& A,
                               int pivot_idx) {
  vector<Color> colors;
  colors.resize(A.size());
  std::array<int, 3> count = {0, 0, 0};
  for (size_t i = 0; i < A.size(); i++) {
    count[A[i]]++;
    colors[i] = static_cast<Color>(A[i]);
  }
  Color pivot = colors[pivot_idx];

  timer.Start();
  DutchFlagPartition(pivot_idx, &colors);
  timer.Stop();

  int i = 0;
  while (i < colors.size() && colors[i] < pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] == pivot) {
    count[colors[i]]--;
    ++i;
  }

  while (i < colors.size() && colors[i] > pivot) {
    count[colors[i]]--;
    ++i;
  }

  if (i != colors.size() || count != std::array<int, 3>{0, 0, 0}) {
    throw TestFailureException("Invalid output");
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "A", "pivot_idx"};
  generic_test_main(argc, argv, param_names, "dutch_national_flag.tsv",
                    &DutchFlagPartitionWrapper);
  return 0;
}
