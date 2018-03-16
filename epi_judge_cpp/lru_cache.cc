#include <vector>
#include <unordered_map>
#include <list>
#include <deque>
#include <utility>
#include <algorithm>
#include <iostream>
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_utils_serialization_traits.h"


using std::unordered_map;
using std::pair;
using std::list;



// O(1) look up time
// O(1) insert
class LruCache {
    list<int> dq; // double ended queue storing price to provide eviction candidate
    unordered_map<int,list<int>::iterator > cache;  // map isbn to price
    size_t cache_size = 0;
public:
    LruCache(size_t capacity):cache_size(capacity){};

  int Lookup(int isbn) {
      unordered_map<int, list<int>::iterator >::iterator iter = cache.find(isbn);
      if (iter!=cache.end()) {
          // a cache hit
          // move the hit  to the front of the list
          std::cout<<isbn <<" cache hit "<< iter->first<<std::endl;
          int updated_price = *iter->second;
          dq.erase(iter->second);
          dq.insert(dq.begin(),updated_price);
          cache[isbn] = dq.begin();
          return updated_price;
      }
    return -1;
  }

  void Insert(int isbn, int price) {
    // check if the size is full
      if (cache.size() == cache_size) {
          // evict an entry
          auto dq_iter = dq.end();
          // possible to do O(1)?
          for (auto iter = cache.begin(); iter!=cache.end();iter++) {
              if (iter->second == dq_iter) {
                  std::cout<<"evict "<< iter->first << ", " << *iter->second << std::endl;
                  cache.erase(iter);
                  break;
              }
          }
          dq.pop_back();
      }
      // insert
      std::cout<<"inserting "<< isbn <<"," << price<<std::endl;
      dq.insert(dq.begin(),price);
      cache[isbn] = dq.begin();
      for (auto &iter: dq) {
          std::cout<<iter << " ";
      }
      std::cout<<std::endl;
      return;
  }

  bool Erase(int isbn) {
      const auto &iter = cache.find(isbn);
      if (iter!=cache.end()) {
          dq.erase(iter->second);
          cache.erase(iter);
          return true;
      }
    return false;
  }
};

struct Op {
  std::string code;
  int arg1;
  int arg2;
};

template <>
struct SerializationTraits<Op> : UserSerTraits<Op, std::string, int, int> {};

void RunTest(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailureException("Lookup: expected " +
                                   std::to_string(cmd.arg2) + ", got " +
                                   std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailureException("Erase: expected " +
                                   std::to_string(cmd.arg2) + ", got " +
                                   std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"commands"};
  generic_test_main(argc, argv, param_names, "lru_cache.tsv", &RunTest);
  return 0;
}
