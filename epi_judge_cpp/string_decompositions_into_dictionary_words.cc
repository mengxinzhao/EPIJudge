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

bool MatchAllWords(const string &s,const unordered_map<string,int> &dict,int start_index,int word_len,int num_words ) {
    unordered_map<string,int> checker(dict);
    for(size_t i=0; i< num_words; i++){
        string word = s.substr(start_index + i* word_len, word_len);
        auto iter = dict.find(word);
        if (iter == dict.end())
            return false;
        else {
            checker[word]--;
            if (checker[word] == 0)
                checker.erase(word);
        }
        if (checker.empty())
            return true;
    }
    return false;
}

// overall running complexity is
// O(N*M*m):N:number of all possible matches. M: number of words in dictionary m: word length of the words dictionary
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
        if (MatchAllWords(s,dict,i,word_len, words.size()))
            result.push_back(i);
    }
    
    return result;
}
#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"s", "words"};
  generic_test_main(argc, argv, param_names,
                    "string_decompositions_into_dictionary_words.tsv",
                    &FindAllSubstrings2);
  return 0;
}
