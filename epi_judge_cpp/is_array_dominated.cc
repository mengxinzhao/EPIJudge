#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::vector;
using std::sort;
using std::min;
class Team {
 public:
  explicit Team(const vector<int>& height) {
    transform(begin(height), end(height), back_inserter(players_),
              [](int h) { return Player{h}; });
  }

  // Checks if team0 can be placed in front of team1.
  // sort the two teams by height. Team0 ith placement needs to be shorter than team1 ith placement
  static bool ValidPlacementExists(const Team& team0, const Team& team1) {
      vector<Player> sorted0 = team0.get_sorted_players();
      vector<Player> sorted1 = team1.get_sorted_players();
      for (int i=0; i < min(sorted0.size(),sorted1.size()); i++) {
          if (sorted0[i] < sorted1[i] == false)
              return false;
      }
      

    return true;
  }

 private:
  struct Player {
    bool operator<(const Player& that) const { return height < that.height; }

    int height;
  };
    
    vector<Player> get_sorted_players() const {
        vector<Player> sorted(players_);
        sort(sorted.begin(),sorted.end());
        return sorted;
  }

  vector<Player> players_;
};

void ValidPlacementExistsWrapper(TestTimer& timer, const vector<int>& team0,
                                 const vector<int>& team1, bool expected_01,
                                 bool expected_10) {
  Team t0(team0), t1(team1);
  timer.Start();
  if (Team::ValidPlacementExists(t0, t1) != expected_01 &&
      Team::ValidPlacementExists(t1, t0) != expected_10) {
    throw TestFailureException("");
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "team0", "team1", "expected_01",
                                       "expected_10"};
  generic_test_main(argc, argv, param_names, "is_array_dominated.tsv",
                    &ValidPlacementExistsWrapper);
  return 0;
}
