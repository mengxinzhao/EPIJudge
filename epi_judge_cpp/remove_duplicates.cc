#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/test_utils_serialization_traits.h"

using std::string;
using std::vector;
using std::set;
using std::hash;
using std::unordered_map;

struct Name {
  bool operator<(const Name& that) const {
    return first_name != that.first_name ? first_name < that.first_name
                                         : last_name < that.last_name;
  }

  string first_name, last_name;
};

struct nameCompare {
    bool operator()(const Name &n1, const Name &n2) const {
        return n1.first_name == n2.first_name && n2.last_name == n2.last_name;
    }
};

struct nameHash {
    size_t operator() (const Name &name) const {
        return hash<string>()(name.first_name) ^ (hash<string>()(name.last_name)>>1);
    }
};

// use hash
void EliminateDuplicate(vector<Name>* names) {
    unordered_map<Name,int,nameHash,nameCompare>name_map;
    vector<Name> &n = *names;
    for (int i=0; i<n.size();i++) {
        name_map[n[i]]++;
    }
    n.clear();
    for ( auto &iter:name_map) {
        n.push_back(iter.first);
    }
    return ;
}

// use set
// seems to be the same speed with hash
void EliminateDuplicate2(vector<Name>* names) {
    set<Name>name_map;
    vector<Name> &n = *names;
    for (int i=0; i<n.size();i++) {
        name_map.insert(n[i]);
    }
    n.clear();
    for ( auto &iter:name_map) {
        n.push_back(iter);
    }
    return ;
}

template <>
struct SerializationTraits<Name>
    : UserSerTraits<Name, std::string, std::string> {};

std::ostream& operator<<(std::ostream& out, const Name& n) {
  return out << n.first_name;
}

vector<Name> EliminateDuplicateWrapper(vector<Name> names) {
  EliminateDuplicate(&names);
  return names;
}

bool Comp(vector<std::string> expected, vector<Name> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return std::equal(
      begin(expected), end(expected), begin(result), end(result),
      [](const std::string& s, const Name& n) { return s == n.first_name; });
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"names"};
  generic_test_main(argc, argv, param_names, "remove_duplicates.tsv",
                    &EliminateDuplicateWrapper, &Comp);
  return 0;
}
