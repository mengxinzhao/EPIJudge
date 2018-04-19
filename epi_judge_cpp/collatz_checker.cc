#include <vector>
#include <unordered_map>
#include <cstdint>
#include <iostream>
using std::vector;
using std::unordered_map;

bool TestCollatzConjectureHelper(int n , int parent, unordered_map<int, int> &cache ) {
    //if it is in the cache good
    //std::cout<<"checking "<< n << ", parent: "<< parent << std::endl;
    auto iter = cache.find(n);
    if (iter!= cache.end() && iter->second == 1) {
        cache[parent] = 1;
        return true;
    }
    
    //reduce to an  odd number
    int k = n;
    while (k%2==0 && k/2 >0)
        k =k/2;
    //std::cout<<"reduced  to "<<  k <<std::endl;
    //now k is an odd number
    if (k==1) {
        cache[parent] = 1;
        cache[n] = 1;
        return true;
    }else {
        if ( TestCollatzConjectureHelper(3*k+1,n,cache)) {
            cache[parent] = 1;
            cache[n] = 1;
            return true;
        }else {
            cache[parent] = 3*k+1;
            cache[n] = 3*k+1;
        }
    }
    return false;
}
bool TestCollatzConjecture(int n) {
    unordered_map<int, int> cache;
    // those are already known
    cache[1] = 1;
    cache[2] = 1;
    
    return TestCollatzConjectureHelper(n,n,cache);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"n"};
  generic_test_main(argc, argv, param_names, "collatz_checker.tsv",
                    &TestCollatzConjecture);
  return 0;
}
