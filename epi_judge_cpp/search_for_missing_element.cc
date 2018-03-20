#include <vector>
#include <iostream>
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;

struct DuplicateAndMissing {
  int duplicate, missing;
};

// sum(A)= sum(Z)+ d -m
// square_sum(A) = square_sum(Z) + d^d - m^m
// d + m = (square_sum(A) - square_sum(Z))/(sum(A) - sum(Z))
DuplicateAndMissing FindDuplicateMissing(const vector<int>& A) {
    int sum=0, square_sum =0;
    for (int i=0;i < A.size();i++) {
        sum += A[i]-i;
        square_sum +=  A[i]*A[i]-i*i;
    }

  return {(square_sum / sum + sum)/2, (square_sum / sum - sum)/2 };
}

// using XOR
// A:  0....d d ....N-1
// Z:  0....d m ....N-1
// A xor Z = d xor m. we know d and m diff in those many bits. take lowest diff bit
// use d xor m to scan through A. if d xor m & A[i] = 1 A[i] bit is  set else cleared. this splits A into 2 parts [the numbers who has the same bit set, the numbers who has the same bit clean]
// same as Z.
// xor A and Z's bit same part. there will be one element appearing twice ==> this is either d or m
DuplicateAndMissing FindDuplicateMissing2(const vector<int>& A) {
    int d_xor_m = 0;
    for (int i=0; i< A.size();i++) {
        d_xor_m^=A[i] ^i;
    }
    int ldb = d_xor_m & (~(d_xor_m-1)); // lowest diff bit
    int set = 0;
    for (int i=0; i< A.size();i++) {
        if (A[i] & ldb)
            set ^=A[i];
        if (i & ldb)
            set ^=i;
    }
    //final pass through A. if set xor A[i] == 0 the dup is found else set is the missing
    for (int i=0; i< A.size();i++){
        if ((A[i] ^ set) == 0)
            return {set , set xor d_xor_m};
    }
    return {d_xor_m xor set,set};
    
}

template <>
struct SerializationTraits<DuplicateAndMissing>
    : UserSerTraits<DuplicateAndMissing, int, int> {};

bool operator==(const DuplicateAndMissing& lhs,
                const DuplicateAndMissing& rhs) {
  return std::tie(lhs.duplicate, lhs.missing) ==
         std::tie(rhs.duplicate, rhs.missing);
}

std::ostream& operator<<(std::ostream& out, const DuplicateAndMissing& x) {
  return out << "duplicate: " << x.duplicate << ", missing: " << x.missing;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "find_missing_and_duplicate.tsv",
                    &FindDuplicateMissing2);
  return 0;
}
