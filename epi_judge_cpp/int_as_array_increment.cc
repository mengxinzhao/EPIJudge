#include <vector>
#include <iostream>

using std::vector;

vector<int> PlusOne(vector<int> A) {
  // Implement this placeholder.
  // assume the LSB is in A[last_bit].
  //  value < 1,2,9 >   129
  //  index [ 0,1,2 ]
#if DEBUG
  for (int i=A.size()-1;i>=0;i--)
    std::cout<<A[i];
  std::cout<<std::endl;
#endif

  int MSB = A[0];

  if (MSB >=0) {
    int carry_bit = ((A[A.size()-1] + 1 )> 9);
    A[A.size()-1] = (A[A.size()-1] + 1 ) %10;
    for (int i = A.size()-2; i >=0; i--) {
      if (A[i] + carry_bit > 9) {
        A[i] = 0;
        carry_bit = 1;
      } else {
        A[i] = A[i] + carry_bit;
        carry_bit = 0;
      }
    }
    if (carry_bit)
      A.insert(A.begin(),carry_bit);
  } else {
    int borrow_bit = ((A[A.size()-1]-1)< 0) ;
    A[A.size()-1] = 10 +A[A.size()-1]-1;
    for (int i = A.size()-2; i >=0; i--) {
      if (A[i] - borrow_bit < 0) {
        A[i] = 10 -(A[i] - borrow_bit);
        borrow_bit = 1;
      } else {
        A[i] = A[i] - borrow_bit;
        borrow_bit = 0;
      }
    }
    // all borrowed. Remove the MSB bit. make sign on the next bit
    if (A[0] == 0 ) {
      A.erase(A.begin());
      A[0] *= (-1);
    }
  }
  return A;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "int_as_array_increment.tsv",
                    &PlusOne);
  return 0;
}
