package epi;

import epi.test_framework.EpiTest;
import epi.test_framework.GenericTestHandler;

import java.util.List;

public class KthLargestInArray {
  // The numbering starts from one, i.e., if A = [3,1,-1,2] then
  // findKthLargest(A, 1) returns 3, findKthLargest(A, 2) returns 2,
  // findKthLargest(A, 3) returns 1, and findKthLargest(A, 4) returns -1.
  public static int findKthLargest(List<Integer> A, int k) {
    // Implement this placeholder.
    return 0;
  }

  @EpiTest(testfile = "kth_largest_in_array.tsv")
  public static int findKthLargestWrapper(int k, List<Integer> A) {
    return findKthLargest(A, k);
  }

  public static void main(String[] args) {
    GenericTestHandler.executeTestsByAnnotation(
        new Object() {}.getClass().getEnclosingClass(), args);
  }
}
