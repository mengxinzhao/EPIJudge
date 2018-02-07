#include <vector>
#include <iostream>

using std::vector;

#include <algorithm>
void print(vector<int> A) {
	for (int i=0;i< A.size();i++)
		std::cout<<A[i]<<" ";
	std::cout<<std::endl;
	return ;
}

void nextPermutation(vector<int>A, int m, int n,vector<vector<int>> &result ) {
	if (m == n) {
		result.push_back(A);
		print(A);
		return ;
	}
	for (int i = m; i <= n;i++) {
		//std::cout<<"swap " << m << "and " << i<<std::endl;
		std::swap(A[m],A[i]);
		nextPermutation(A,m+1,n,result);
		std::swap(A[m],A[i]);
	}
	return ;
}
vector<vector<int>> Permutations(vector<int> A) {
  // Implement this placeholder.
  // permutate all elements in a A
  // array:  4 6 7
  // index:  0 1 2
	// perm:   4 <--> 4  m =0 , n = 2, i=0
	//         4 | per(6,7) m = 1, n  = 2
	//                 6 | per(7,7) ---> return 4 6 7
	//                 7 | per (6,6) --> return 4 7 6
	// perm:   4 <--> 6  m=1, i = 1
	//         6 | per (4,7)
	//                  4 | per(7,7) --> return 6 4 7
	//                  7 | per(4,4) --> return 6 7 4
	// perm:   4 <--> 7  m=1, i = 2
	//         7 | per (6,4)
	//                  6 | per(4,4) --> return 7 6 4
	//                  4 | per(6,6) --> return 7 4 6
  vector<vector<int>> vals;
	nextPermutation(A,0,A.size()-1,vals);

  return vals;
}

#include "test_framework/test_utils_generic_main.h"
#if 0
int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"A"};
  generic_test_main(argc, argv, param_names, "permutations.tsv", &Permutations,
                    &UnorderedComparator<vector<vector<int>>>);
  return 0;
}
#endif
int main() {
	vector<int> A;
	A.push_back(4);
	A.push_back(6);
	A.push_back(7);
	vector<vector<int> > result = Permutations(A);
	return 0;
}
