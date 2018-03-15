#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

// map each char to its frequency
// O(N+M+m) complexity N : letter_text length, M magzine_test length, m letter_freq length
bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
    unordered_map<char, int> letter_freq;
    unordered_map<char, int> magazine_freq;
    for (const auto &ch: letter_text){
        letter_freq[ch]++;
    }
    for (const auto &ch: magazine_text){
        magazine_freq[ch]++;
    }
    for (const auto &iter: letter_freq) {
        if (magazine_freq.find(iter.first) == magazine_freq.end() || iter.second > magazine_freq[iter.first])
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
