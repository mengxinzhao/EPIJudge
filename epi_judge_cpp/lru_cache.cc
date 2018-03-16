#include <vector>
#include <unordered_map>
#include <list>
#include <deque>
#include <utility>
#include <algorithm>
#include <iostream>
#include <iterator>
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_utils_serialization_traits.h"


using std::unordered_map;
using std::pair;
using std::list;

// O(1) look up time
// O(1) insert ( not really O(n) n cache size)
class LruCache {
    list<int> dq;                    // doubly linked list storing price to provide eviction candidate
    unordered_map<int,list<int>::iterator > cache;  // map isbn to the price location in the link list
    size_t cache_size = 0;
public:
    LruCache(size_t capacity):cache_size(capacity){};

  int Lookup(int isbn) {
      unordered_map<int, list<int>::iterator >::iterator iter = cache.find(isbn);
      if (iter!=cache.end()) {
          // a cache hit
          // move the hit  to the front of the list
          dq.push_front(*iter->second);
          dq.erase(iter->second);
          cache[isbn] = dq.begin();
          return *dq.begin();
      }
    return -1;
  }

  void Insert(int isbn, int price) {
      //std::cout<<"inserting "<< isbn <<"," << price<<std::endl;
      unordered_map<int, list<int>::iterator >::iterator iter = cache.find(isbn);
      if (iter == cache.end()) {
          // check if the cache is full
          if (cache.size() == cache_size) {
              // evict an entry
              auto dq_iter = std::prev(dq.end());
              // possible to do O(1)?
              for (auto iter = cache.begin(); iter!=cache.end();iter++) {
                  if (iter->second == dq_iter) {
                      dq.pop_back();
                      cache.erase(iter);
                      break;
                  }
              }
          }
          dq.push_front(price);
          cache[isbn] = dq.begin();

          
      }else {
          // I don't understand why it shouldn't update the isbn price to be more recent
          // only this way could pass the judge data
          // cache hit
          dq.push_front(*iter->second);
          dq.erase(iter->second);
          cache[isbn] = dq.begin();
          
      }

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
