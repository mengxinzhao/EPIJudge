#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
using std::vector;
using std::swap;

void printA(vector<int> &A,int left ,int right) {
    for (int i=left; i <=right;i++)
        std::cout<<A[i] <<" ";
    std::cout<<std::endl;
}

//standard implemenation (pseudo codes given by standford aglorithm class)
int partition(vector<int> &A, int left, int right, int pivot_idx) {
    int p_idx = left+1;   //point to the 1st element smaller than pivot
    // use 1st as pivot for the easiness of implementation
    swap(A[pivot_idx], A[left]);
    int pivot = A[left];
    
    for (int i=left+1; i <=right; i++){
        if (A[i] > pivot) {
            swap(A[i],A[p_idx]);
            p_idx++;
        }
    }
    swap(A[left], A[p_idx-1]) ; // fill the final pivot to the right place
    return p_idx-1;
}

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
    // pick a pivot in the array and partition the array such as
    // all numbers bigger than pivot is on its left and smaller/equal to  than pivot
    // on its right
    // if the pivot index  =  k-1 done
    // if pivot index > k-1 the element is in [0, p-1]
    // if pivot index < k-1 the element is in [p+1,n-1].
	vector<int> &A = *A_ptr;
	int left = 0;
	int right= A.size()-1;
	while(left <= right) {
		int pivot_index = partition(A, left, right, left); // always choose left as pivot
		if (pivot_index > k - 1) {
			right = pivot_index-1;
		} else if (pivot_index == k - 1)
			return A[pivot_index];
		else if (pivot_index < k - 1) {
			left = pivot_index+1;
		}
	}
    return -1;
}

int FindKthLargestWrapper(int k, vector<int>& A) {
  return FindKthLargest(k, &A);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"k", "A"};
  generic_test_main(argc, argv, param_names, "kth_largest_in_array.tsv",
                    &FindKthLargestWrapper);
//    std::vector<int>A({101, 99, 103, 93, 67, 84, 77, 68, 77, 64, 61, 84});
//    // 101, 103, 99, 93, ....
//    int index = partition(A,0,A.size()-1,1); //
//    printA(A,0,A.size()-1);
//    std::cout<<"pivot index " << index<<std::endl;
	return 0;
}
