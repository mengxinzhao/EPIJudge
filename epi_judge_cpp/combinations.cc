#include <vector>
#include <iostream>

using std::vector;

void generateCombination(vector<vector<int>> &result,vector<int> input, vector<int> curr,
                         int start_index,int bits_remain, bool chosen ) {
	// curr: the curr result. can't use reference. otherwise the later result will mess up the previous result
	// bits_remain: number of choice remaining from [start+1 , end]
	//std::cout<<"start: "<<start_index<< " chosen " <<chosen<< " bits " << bits_remain <<std::endl;
	if (bits_remain < 0 || start_index > input.size()-1)
		return ;

	else {
		// choose the current bit.
		if (chosen)
			curr.push_back(input[start_index]);

		if (bits_remain <= 0) {
			result.push_back(curr);
			return;
		}
		// choose start_index+1, and remaining bits_remain-1 from the rest
		generateCombination(result, input, curr, start_index + 1, bits_remain-1, true);
		// all  bits_remain from the rest
		generateCombination(result, input, curr, start_index + 1, bits_remain, false);

	}

}

vector<vector<int>> Combinations(int n, int k) {
  // Implement this placeholder.
	if (k>n|| n<=0 || k<=0)
		return {{}};
	vector<vector<int> > results;
	vector<int> input, first({});
	// have input
	for (int i=1;i<=n;i++)
		input.push_back(i);

	generateCombination(results,input,first,0,k-1, true );  //first bit chosen, choose k-1 from the rest
	generateCombination(results,input,first,0,k, false ); // first bit not chosen choose k from the rest
  return results;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "combinations.tsv", &Combinations,
                    &UnorderedComparator<std::vector<std::vector<int>>>);
  return 0;
}
