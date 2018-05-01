#include <vector>
#include <set>
#include <utility>
#include <iostream>

using std::vector;
using std::move;

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
	// set 4 5 6
    //     {}, {4},{5},{6}, {4,5}, {5,6}, {4,6}, {4,5,6}
    //
    vector<vector<int>> results;
    if (input_set.empty())
        return {{}};

    vector<int> first ({});

    generateSet(results,input_set,first,0,true);
    generateSet(results,input_set,first,0,false);
  return results;
}

// subset[i] = A[i] U subset[i-1]
// subset[0] = {}
// i: number of element
// subset[i-1] element 2^(i-1)
// O(n * 2^(n)) run time complexity
vector<vector<int>> GeneratePowerSet2(const vector<int>& input_set) {

    vector<vector<int>> subset;
    vector<vector<int>> result({{}});
    
    for (int i=1;i<=input_set.size();i++) {
        //vector<vector<int>> subset = move(result);
        vector<vector<int>> subset(result);
        for (int j=0; j< subset.size();j++) {
            // subset[i] = A[i] U subset[i-1]
            //result.push_back(subset[j]);
            subset[j].push_back(input_set[i-1]);
            result.push_back(subset[j]);
            
        }
    }
    return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"input_set"};
  generic_test_main(argc, argv, param_names, "power_set.tsv", &GeneratePowerSet2,
                    &UnorderedComparator<vector<vector<int>>>);
  return 0;
}
