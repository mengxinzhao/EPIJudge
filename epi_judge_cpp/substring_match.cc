#include <string>
#include <cstddef>
#include <iostream>
#include <cstdint>
#include <cmath>

using std::string;

// Returns the index of the first character of the substring if found, -1
// otherwise.
// implementation refers to MIT algorithm class
// hash function:
// H(0...k-1) = {c0* a^(k-1) + c1 * a^(k-2) + ...ck-2 * a + ck-1 } mod M
// a constant
// c1...ck input char
// k length of the string
// next hash
// H(1..k) =  c1* a^(k-1) + c2 * a^(k-2) + ...ck-1 * a + ck = a( H(0...k-1) - c0*a^(k-1)) + ck   mod M

int A = 3; // base too big might  have overflow problem

// integer pow
uint64_t pow(int base, int exp) {
    uint64_t power = 1;
    for (int i=0; i<exp; i++) {
        power *= base;
    }
    return power;
}
uint64_t hash(const string &s) {
    int H = 0;
    int k = s.length();
    for (size_t i=0; i< k;i++) {
        H = ((H * A  + (s[i] - 0)));
    }
    return H ;
}


int RabinKarp(const string &t, const string &s) {
    if (s.length() > t.length())
        return -1;
    if (s.length() == 0) // s is an emtry string
        return 0;

    uint64_t Hs = hash(s);
    uint64_t Ht = hash(t.substr(0, s.length()));
    int k = s.length();

    if (Hs == Ht) {
        if (t.compare(0, s.length(),s) == 0)
            return 0;
    }

    uint64_t power = pow(A, (k-1)) ;
    for (int i=s.length(); i< t.length();i++) {
        // move the window
        Ht -= t[i - k ] * power;
        Ht = Ht * A + t[i];
        if (Ht == Hs){
            // check if it is a true match
            if (t.compare(i-k+1,k,s) == 0)
                return i -k+1;
        }
    }
  return -1;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char *argv[]) {
  std::vector<std::string> param_names{"t", "s"};
  generic_test_main(argc, argv, param_names, "substring_match.tsv", &RabinKarp);
  return 0;
}
