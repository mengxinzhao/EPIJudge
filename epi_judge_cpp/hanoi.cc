#include <array>
#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"

using std::array;
using std::stack;
using std::vector;

const int kNumPegs = 3;

void move(int num,vector<vector<int>>  &towers,int from, int to,int through ){
	if (num<=0)
		return;
	move(num-1,towers,from,through,to);
	towers[to].push_back(towers[from].back());
	towers[from].pop_back();
	std::cout<<"move from "<<from<<" to "<<to<< std::endl;
	move(num-1,towers,through,to,from);

}

vector<vector<int>> ComputeTowerHanoi(int num_rings) {
  // Implement this placeholder.
	vector<vector<int>> towers(3, vector<int>());
	for(int i = num_rings;i>=1;i--){
		towers[0].push_back(i);
	}
	move(num_rings,towers,0,1,2);

  return towers;
}

void ComputeTowerHanoiWrapper(TestTimer& timer, int num_rings) {
  array<stack<int>, kNumPegs> pegs;
  for (int i = num_rings; i >= 1; --i) {
    pegs[0].push(i);
  }
  timer.Start();
  vector<vector<int>> result = ComputeTowerHanoi(num_rings);
  timer.Stop();

  for (const vector<int>& operation : result) {
    int from_peg = operation[0], to_peg = operation[1];
    if (!pegs[to_peg].empty() && pegs[from_peg].top() >= pegs[to_peg].top()) {
      throw TestFailureException("Illegal move from " +
                                 std::to_string(pegs[from_peg].top()) + " to " +
                                 std::to_string(pegs[to_peg].top()));
    }
    pegs[to_peg].push(pegs[from_peg].top());
    pegs[from_peg].pop();
  }
  array<stack<int>, kNumPegs> expected_pegs1, expected_pegs2;
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs1[1].push(i);
  }
  for (int i = num_rings; i >= 1; --i) {
    expected_pegs2[2].push(i);
  }
  if (pegs != expected_pegs1 && pegs != expected_pegs2) {
    throw TestFailureException("Pegs doesn't place in the right configuration");
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "hanoi.tsv", &ComputeTowerHanoiWrapper);
  return 0;
}
