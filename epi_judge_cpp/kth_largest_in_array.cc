#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
using std::vector;

void printA(vector<int> &A,int left ,int right) {
	std::cout<<"============================"<<std::endl;
	for (int i=left; i <=right;i++)
		std::cout<<A[i] <<" ";
	std::cout<<std::endl;
}

// partition the array such as all numbers bigger than pivot are in the left to pivot
// start from the right . If the A[right] <= pivot
// pivot needs to be put before right
int partition(vector<int>  &A, int left, int right, int pivot_idx) {
	int p_idx = right; // new pivot index
	int pivot = A[pivot_idx];
	std::swap(A[pivot_idx],A[left]);
	while(left < right) {
		if (A[right] <= pivot) {
			std::swap(A[right],A[p_idx]);
			p_idx--;

		}
		right--;
	}
	// the first element before is less or equal than pivot
	if (p_idx <0) {
		std::cout<<"p_idx less than 0 " << std::endl;
		std::cout<<"pivot " << pivot<<std::endl;
		p_idx = 0;
	}
	std::swap(A[left],A[p_idx]);
	return p_idx;
}

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int>* A_ptr) {
  // Implement this placeholder.
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
		//std::cout << "pivot_index: " << pivot_index << std::endl;
		//printA(A,left,right);
		if (pivot_index > k - 1) {
			right = pivot_index-1;
		} else if (pivot_index == k - 1)
			return A[pivot_index];
		else if (pivot_index < k - 1) {
			left = pivot_index+1;
		}
	}
}


int FindKthLargestWrapper(int k, vector<int>& v) {
  return FindKthLargest(k, &v);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "kth_largest_in_array.tsv",
                    &FindKthLargestWrapper);
	//std::vector<int>A({101, 99, 103, 93, 67, 86, 77, 68, 62, 64, 61, 84});
	//int index = partition(A,0,A.size()-1,1); //  pivot = 68
	//printA(A,0,A.size()-1);
	//std::cout<<"pivot index " << index<<std::endl;
	return 0;
}
