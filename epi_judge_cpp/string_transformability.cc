#include <string>
#include <unordered_set>
#include <queue>
#include <utility>
using std::string;
using std::unordered_set;
using std::queue;
using std::pair;

// construct the graph such that each vertex represent a word and
// each edge represent a one-letter transformation from one word to anotherr.
// The least steps of transformation is found through BFS search from s to t
// The distance is the least steps.


struct Candidate {
    string word;
    int distance;
    Candidate(string _word, int _dist):word(_word), distance(_dist) {}
};

int TransformString(unordered_set<string> D, const string& s, const string& t) {
  // Implement this placeholder.
    queue<Candidate> dict_q;
    dict_q.emplace(s,0);
    D.erase(s); // marked as vistied
    while(!dict_q.empty()){
        Candidate top = dict_q.front();
        dict_q.pop();
        if (top.word == t)
            return top.distance;
        
        // try all possbile candidate with one hop away
        // 26 letters permutate on all position on that word
        for (int pos = 0; pos < top.word.length();pos++) {
            for (char c='a'; c<='z';c++) {
                string new_word = top.word;
                if (c!= top.word[pos])
                    new_word[pos] = c;
                if (D.find(new_word) != D.end() ) {
                    D.erase(new_word);
                    dict_q.emplace(new_word, top.distance+1);
                    
                }
            }
        }
    }
    
  return -1;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"D", "s", "t"};
  generic_test_main(argc, argv, param_names, "string_transformability.tsv",
                    &TransformString);
  return 0;
}
