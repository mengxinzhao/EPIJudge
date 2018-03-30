#include <string>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>
using std::string;
using std::unordered_set;
using std::vector;
using std::min;
//if string[0:N] is not a word
// DP[N] =  DP[N-k] + string[N-k+1:N] if  string[N-k+1:i] is a word for k = 1,...N
//else  DP[N] = string[0:N]
//solution DP[N]
//O(n!)
bool DecomposeIntoDictionaryWordsHelper(const string &domain,const unordered_set<string>& dictionary,
                                        int index, vector<string> &curr_solution) {
    
    // all for possbilities, try them all
    string word = string(domain.begin(),domain.begin()+index+1);
    if (dictionary.find(word) != dictionary.end()) {
        curr_solution.push_back(word);
        return true;
    }
    //for  (int i=1; i<=index;i++) {
    for  (int i=index; i>=0;i--){
        word = string(domain.begin()+index-i+1,domain.begin()+index+1);
        if (dictionary.find( word)!= dictionary.end()) {
            // word exists, go for next word
            curr_solution.push_back(word);
            bool decomposable = DecomposeIntoDictionaryWordsHelper(domain,dictionary, index-i, curr_solution);
            if (!decomposable) {
                curr_solution.pop_back();
                continue;
            }else
                return true;
        }
        else
            continue;
    }
            
    // no solution at all
    return false;  //triger backtracking
}

// O(n^3) run time complexity
vector<string> DecomposeIntoDictionaryWords_DP(const string& domain, const unordered_set<string>& dictionary) {
    // track if string[i,j] is decomposable
    vector<vector<bool>> DP(domain.size(),vector<bool>(domain.size(),false));
    vector<string> result;
    // bottom up
    for (int i=0;i < domain.size();i++){
        for (int j=i; j< domain.size();j++) {
            string word(domain.begin()+i, domain.begin()+j+1);
            //std::cout<<"test: " << word<<std::endl;
            if (dictionary.find(word) != dictionary.end())
                DP[i][j] = true;
            else {
                // try all possible ways
                // DP[i,j] =  DP[i,j-k] && string[j-k+1:j] in dictionary if  string[j-k+1:j] is a word for k = 1,...j-i
                for (int k=1; k<=j-i;k++) {
                    string substr = string(domain.begin()+j-k+1,domain.begin()+j+1);
                    //std::cout<<"test substr: " <<i<<","<<j<<","<<k<<" "<< substr<<std::endl;
                    if ( DP[i][j-k] && dictionary.find(substr) != dictionary.end()){
                        DP[i][j] = true;
                        break;
                    }
                }
            }
        }
    }
    
    int i=0;
    if (DP[0][domain.size()-1]) {
        for (int col = 0; col <domain.size() && i< domain.size(); col++) {
            if (DP[i][col] == true) {
                //std::cout<<string(domain.begin()+i, domain.begin()+col+1)<<std::endl;
                if ((col+1 < domain.size()&&  DP[col+1][domain.size()-1]) || col == domain.size()-1) {
                    result.emplace_back(domain.begin()+i, domain.begin()+col+1);
                    i = col+1;
                }
            }

        }
    }
    return result;
}

// O(n^3) run time complexity
vector<string> DecomposeIntoDictionaryWords_optimal(const string& domain, const unordered_set<string>& dictionary) {
    // track if string[i,j] can be decomposed to least amount of words
    vector<vector<int>> DP(domain.size(),vector<int>(domain.size(),INT_MAX));
    vector<string> result;
    // bottom up
    for (int i=0;i < domain.size();i++){
        for (int j=i; j< domain.size();j++) {
            string word(domain.begin()+i, domain.begin()+j+1);
            //std::cout<<"test: " << word<<std::endl;
            if (dictionary.find(word) != dictionary.end())
                DP[i][j] = 1;
            else {
                // try all possible ways.
                // DP[i,j] =  DP[i,j-k] && string[j-k+1:j] in dictionary if  string[j-k+1:j] is a word for k = 1,...j-i
                for (int k=1; k<=j-i;k++) {
                    string substr = string(domain.begin()+j-k+1,domain.begin()+j+1);
                    //std::cout<<"test substr: " <<i<<","<<j<<","<<k<<" "<< substr<<std::endl;
                    if ( DP[i][j-k]< INT_MAX  && dictionary.find(substr) != dictionary.end()){
                        DP[i][j] = min(DP[i][j],1+DP[i][j-k]);
                    }
                }
            }
        }
    }
#if debug
    for (int i=0; i< domain.size();i++){
        for (int j=i; j< domain.size();j++)
            std::cout<<i<<"->"<<j<<": "<<DP[i][j] <<", ";
        std::cout<<std::endl;
    }
#endif
    // DP[0][domain.size()-1] the mininum word decomposition for the given string
    int i=0;
    if (DP[0][domain.size()-1] < INT_MAX) {
        int min_step = DP[0][domain.size()-1];
        for (int col = 0; col <domain.size() && i< domain.size(); col++) {
            if  (min_step == DP[i][col] && col == domain.size()-1) {
                result.emplace_back(domain.begin()+i, domain.begin()+col+1);
                break;
            }
            else if (col+1 < domain.size()  && DP[col+1][domain.size()-1] == min_step -  DP[i][col]) {
#if debug
                std::cout<<string(domain.begin()+i, domain.begin()+col+1)<<std::endl;
#endif
                result.emplace_back(domain.begin()+i, domain.begin()+col+1);
                min_step -=DP[i][col];
                i = col+1;
            }
            
        }
    }
    return result;
}


vector<string> DecomposeIntoDictionaryWords(
    const string& domain, const unordered_set<string>& dictionary) {
    vector<string> solution;
    DecomposeIntoDictionaryWordsHelper(domain,dictionary, domain.length()-1,solution);
    std::reverse(solution.begin(),solution.end());
    return solution;
    
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"domain", "dictionary"};
  generic_test_main(argc, argv, param_names,
                    "is_string_decomposable_into_words.tsv",
                    &DecomposeIntoDictionaryWords_optimal);
  return 0;
}
