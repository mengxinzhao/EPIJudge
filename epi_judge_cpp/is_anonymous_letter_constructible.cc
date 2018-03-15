#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

// map each char to its frequency
// O(N+M) complexity N : letter_text length, M magzine_test length
bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {

    unordered_map<char, int> magazine_freq;
    for (const auto &ch: magazine_text){
        magazine_freq[ch]++;
    }
    
    for (const auto &ch: letter_text){
        if (magazine_freq.find(ch) == magazine_freq.end())
            return false;
        magazine_freq[ch]--;
        if (magazine_freq[ch] < 0)
            return false;
    }
    
  return true;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  generic_test_main(argc, argv, param_names,
                    "is_anonymous_letter_constructible.tsv",
                    &IsLetterConstructibleFromMagazine);
  return 0;
}
