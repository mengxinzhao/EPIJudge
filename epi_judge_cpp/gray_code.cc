#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <bitset>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::vector;
using std::pow;

bool DiffersByOneBit(int x, int y) ;
bool Seen(vector<int>curr_solution, int code) {
    for (int i=0; i< curr_solution.size();i++) {
        if (curr_solution[i] == code)
            return true;
    }
    return false;
}

void GrayCodeHelper(vector<int> &curr_solution, int num_bits) {
    
    if (curr_solution.size()== pow(2,num_bits)) {
        return;
        
    }
    int curr_code = curr_solution.back();
    int next_code = curr_code;
    //can flip num_bit one at a time
    for (int i=0;i<num_bits;i++) {
        next_code = curr_code ^ (1UL<<i);
        if (DiffersByOneBit(next_code,curr_code) && !Seen(curr_solution, next_code) ) {
            curr_solution.push_back(next_code);
            GrayCodeHelper(curr_solution,num_bits);
        }
    }
}

vector<int> GrayCode(int num_bits) {
    vector<int> result({0});
    GrayCodeHelper(result,num_bits);
    return result;
}

bool DiffersByOneBit(int x, int y) {
  int bit_difference = x ^ y;
  return bit_difference && !(bit_difference & (bit_difference - 1));
}

void GrayCodeWrapper(TestTimer& timer, int num_bits) {
  timer.Start();
  vector<int> result = GrayCode(num_bits);
  timer.Stop();

  int expected_size = (1 << num_bits);
  if (result.size() != expected_size) {
    throw TestFailureException("Length mismatch: expected " +
                               std::to_string(expected_size) + ", got " +
                               std::to_string(result.size()));
  }
  for (size_t i = 1; i < result.size(); i++)
    if (!DiffersByOneBit(result[i - 1], result[i])) {
      if (result[i - 1] == result[i]) {
        throw TestFailureException("Two adjacent entries are equal");
      } else {
        throw TestFailureException(
            "Two adjacent entries differ by more than 1 bit");
      }
    }

  std::sort(begin(result), end(result));
  auto uniq = std::unique(begin(result), end(result));
  if (uniq != end(result)) {
    throw TestFailureException(
        "Not all entries are distinct: found " +
        std::to_string(std::distance(uniq, end(result))) + " duplicates");
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "num_bits"};
  generic_test_main(argc, argv, param_names, "gray_code.tsv", &GrayCodeWrapper);
  return 0;
}
