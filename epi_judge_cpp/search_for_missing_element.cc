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
                    &FindDuplicateMissing);
  return 0;
}
