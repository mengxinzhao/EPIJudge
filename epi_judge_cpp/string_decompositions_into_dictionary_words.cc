#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <iostream>
using std::string;
using std::vector;
using std::map;
using std::unordered_map;
using std::find;

// overall running complexity is
// max (O(N*M), O(n*m) N:number of all possible matches. M size of the words dictionary
// n: string length, m: word length of the words dictionary
vector<int> FindAllSubstrings(const string& s, const vector<string>& words) {
    
    if (s.empty() || words.empty())
        return {};
    vector<int> result;
    unordered_map<string,int>dict;
    for (size_t i =0; i< words.size();i++) {
        dict[words[i]]++;
    }
    map<int, string> word_locs;// map index of each matching word to the index in the string
    //find out all possible matches
    size_t word_len = words[0].length();
    for (size_t i=0; i < s.length() && i+word_len<=s.length();i++) {
        string substr = string(s.begin()+i,s.begin()+i+word_len);
        //std::cout<<"testing "<< substr<<std::endl;
        if (dict.find(substr)!= dict.end()) {
            word_locs[i] = substr;
        }
    }
    // iterate through word_locs
    unordered_map<string,int>checker(dict);
    auto iter = word_locs.begin();
    
    while (iter != word_locs.end()){
        auto se_iter = iter;
        int start_index = se_iter->first;
        int index = start_index;
        checker = dict;
        // starting from start_index trying to see if there is a sequence that is
        // concatenate of all dictionary words
        while (index < s.length()) {
            //std::cout<<se_iter->first << ", "<<se_iter->second << std::endl;
            checker[se_iter->second]--;
            if (checker[se_iter->second] == 0)
                checker.erase(se_iter->second);
            
            if (checker.empty()) {
                // find a sequence
                result.push_back(start_index);
                break;
            } else {
                se_iter = word_locs.find(index+word_len);
                if (se_iter!= word_locs.end())
                    index += word_len;
                else
                    break;
            }
        }
        iter++;
    }
    
    return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"s", "words"};
  generic_test_main(argc, argv, param_names,
                    "string_decompositions_into_dictionary_words.tsv",
                    &FindAllSubstrings);
  return 0;
}
