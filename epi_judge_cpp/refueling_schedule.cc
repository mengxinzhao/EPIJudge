#include <vector>

using std::vector;

// gallons[i] is the amount of gas in city i, and distances[i] is the distance
// city i to the next city.
int FindAmpleCity(const vector<int>& gallons, const vector<int>& distances) {
  // Implement this placeholder.
  return 0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"gallons", "distances"};
  generic_test_main(argc, argv, param_names, "refueling_schedule.tsv",
                    &FindAmpleCity);
  return 0;
}
