#include <string>
#include <unordered_map>
#include <map>
#include <utility>
#include <cassert>
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::string;
using std::unordered_map;
using std::map;
using std::pair;

class ClientsCreditsInfo {
 public:
  void Insert(const string& client_id, int c) {
      std::cout<<"adding " << client_id << " " << c<<std::endl;
      if (credits_info.find(client_id) != credits_info.end()) {
          // remove the existing one and  update later
          map<int, string >::iterator loc = credits_info[client_id];
          std::cout<<"existing " << client_id << " " << loc->first<<std::endl;
          clients_info.erase(loc);
          credits_info.erase(client_id);
      }
      pair <map<int, string >::iterator, bool> result  = clients_info.insert(pair< int, string> (c-credit_offset,client_id) );
      credits_info[client_id] = result.first;
      return;
  }

  bool Remove(const string& client_id) {
      if (credits_info.find(client_id)!= credits_info.end()) {
          map<int, string >::iterator loc = credits_info[client_id];
          std::cout<<"removing " << loc->second << " " << loc->first <<std::endl;
          clients_info.erase(loc);
          credits_info.erase(client_id);
          return true;
      }
      return false;
  }

  int Lookup(const string& client_id)  {
      std::cout<<"looking up " << client_id<<std::endl;
      if (credits_info.find(client_id)!= credits_info.end()) {
          map<int, string >::iterator loc  = credits_info[client_id];
          return loc->first + credit_offset;
      }
      return -1;
  }

  // add c credits to all clients
  void AddAll(int C) {
      credit_offset += C;
      return;
  }

  string Max() const {
      auto max_iter  = clients_info.rbegin();
      if (max_iter!= clients_info.rend()) {
          return max_iter->second;
      }
      else
          return "";
  }
private:
    int credit_offset = 0;
    unordered_map<string, map<int, string> :: iterator > credits_info; // map each client to its credits
    map<int, string> clients_info ;// map each credits to its client info
};

struct Operation {
  std::string op;
  std::string s_arg;
  int i_arg;
};

template <>
struct SerializationTraits<Operation>
    : UserSerTraits<Operation, std::string, std::string, int> {};

void ClientsCreditsInfoTester(const std::vector<Operation>& ops) {
  ClientsCreditsInfo credits;
  for (auto& op : ops) {
    if (op.op == "ClientsCreditsInfo") {
      continue;
    } else if (op.op == "remove") {
      bool result = credits.Remove(op.s_arg);
      if (result != op.i_arg) {
        throw TestFailureException("Remove: return value mismatch");
      }
    } else if (op.op == "max") {
      auto result = credits.Max();
      if (result != op.s_arg) {
        throw TestFailureException("Max: return value mismatch");
      }
    } else if (op.op == "insert") {
      credits.Insert(op.s_arg, op.i_arg);
    } else if (op.op == "add_all") {
      credits.AddAll(op.i_arg);
    } else if (op.op == "lookup") {
      auto result = credits.Lookup(op.s_arg);
      if (result != op.i_arg) {
          std::cout<<"expecting: "<<op.i_arg<<std::endl;
        throw TestFailureException("Lookup: return value mismatch ");
      }
    }
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"ops"};
  generic_test_main(argc, argv, param_names, "adding_credits.tsv",
                    &ClientsCreditsInfoTester);
  return 0;
}
