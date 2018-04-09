#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using std::string;
using std::vector;
using std::map;

// Finds the candidates which may occur >= n / k times.
vector<string> SearchFrequentItems(
    int k, vector<string>::const_iterator stream_begin,
    const vector<string>::const_iterator stream_end) {
    
    map<string, int> word_count;
    vector<string> hitters;
    auto &iter = stream_begin;
    int count =0;
    while(iter!= stream_end) {
        word_count[*iter]++;
        count++;
        iter++;
    }
    for (const auto & iter: word_count){
        if (iter.second >count/k )
            hitters.push_back(iter.first);
    }
    return hitters;
}

// candidate occurs > n/k
// at most k outputs
// Misra-Gries heavy hitter algorithm
// O(k) memory
// algorithm from lecture handout
// http://people.csail.mit.edu/moitra/docs/6854lec4.pdf
vector<string> SearchFrequentItems_MG(
   int k, vector<string>::const_iterator stream_begin,
    const vector<string>::const_iterator stream_end) {
    
    map<string, int> distinct_set;
    vector<string> hitters;
    int count =0;
    auto iter = stream_begin;

    while(iter!= stream_end) {
        if (distinct_set.find(*iter)!= distinct_set.end())
            distinct_set[*iter]++;
        else if (distinct_set.size() <=k)
                distinct_set[*iter]++;
        else {
            // throw away item
            auto iterator = distinct_set.begin();
            while(iterator != distinct_set.end()) {
                iterator->second--;
                if (iterator->second == 0){
                    auto to_del = iterator;
                    iterator++;
                    distinct_set.erase(to_del);
                }
                else
                    iterator++;
            }
        }
        iter++;
        count++;
    }
    // there are false positive
    // have to verify it again
    for ( auto & elem: distinct_set) {
        elem.second = 0;
        //std::cout<< elem.first<< ", ";
    }
    //std::cout<<std::endl;
    
    iter = stream_begin;
    while(iter!= stream_end) {
        if (distinct_set.find(*iter)!= distinct_set.end())
            distinct_set[*iter]++;
        iter++;
    }
    //std::cout<<"count/k :" <<float(count)/k << std::endl;
    for (const auto & elem: distinct_set){
        if (elem.second > float(count)/k)
            hitters.push_back(elem.first);
    }
    return hitters;
}

vector<string> SearchFrequentItemsWrapper(int k, vector<string>& stream) {
  return SearchFrequentItems_MG(k, begin(stream), end(stream));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"k", "stream"};
  generic_test_main(argc, argv, param_names, "search_frequent_items.tsv",
                    &SearchFrequentItemsWrapper,
                    &UnorderedComparator<std::vector<std::string>>);
  return 0;
}
