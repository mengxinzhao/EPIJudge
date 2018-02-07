#include <iostream>
#include <vector>
using std::vector;
int delete_key_from_array(vector<int> &A, int key) {
   int j=0;
   for (int i=0;i<A.size();i++) {
      if (A[i] != key) {
         A[j++] = A[i];
   }
 }
   return j;
}


int main() {
   int a[]={3,3,3,5,5,6,1,3, 6};
   vector<int> A(a,a+sizeof(a)/sizeof(int));
   for (int i=0;i<A.size();i++)
   	std::cout<<A[i]<<" ";
   std::cout<<std::endl;
   int len  = delete_key_from_array(A,3);
   std::cout<<"len: "<< len<< std::endl;
   for (int i=0;i<len;i++)
   	std::cout<<A[i]<<" ";
   std::cout<<std::endl;

}
