#include <vector>
#include <set>

using std::vector;

void generateSet(vector<vector<int>> &results,const vector<int> input_set,vector<int> curr_set, int start, bool chosen ) {
	// set 6 4 5
	//     {}, {4},{5},{6}, {4,5}, {5,6}, {4,6}, {4,5,6}
	// recursion
	// _,(4,5)
	// --> _,_,(5)
	//  --> _,_,_, _,_5
	// --> _,4 (5)
	//   --> _,4_,_,    _,4,5
	// 6, (4 ,5)
	// --> 6,_,(5)
	//  --> 6,_,_, 6,_,5
	// --> 6,4,(5)
	//   --> 6,4,_,    6,4,5

	if  (start ==input_set.size()-1) {
		 if (chosen) {
			 curr_set.push_back(input_set[start]);
		 }
		results.push_back(curr_set);

	}else {
		if (chosen) {
			curr_set.push_back(input_set[start]);
		}
		generateSet(results,input_set,curr_set,start+1,true);
		generateSet(results,input_set,curr_set,start+1,false);
	}
}

vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
  // Implement this placeholder.
	// set 4 5 6
	//     O, {4},{5},{6}, {4,5}, {5,6}, {4,6}, {4,5,6}
	//
	vector<vector<int>> results;
	if (input_set.empty())
		return {{}};

	vector<int> first ({});

	generateSet(results,input_set,first,0,true);
	generateSet(results,input_set,first,0,false);
  return results;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "power_set.tsv", &GeneratePowerSet,
                    &UnorderedComparator<vector<vector<int>>>);
  return 0;
}
