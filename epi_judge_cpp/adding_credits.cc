#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <utility>
#include <cassert>
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::string;
using std::unordered_map;
using std::map;
using std::pair;
using std::unordered_set;

class ClientsCreditsInfo {
 public:
  void Insert(const string& client_id, int c) {
      Remove(client_id);
      
      clients_info[c-credit_offset].insert(client_id );
      credits_info[client_id] = c-credit_offset;
      return;
  }

  bool Remove(const string& client_id) {
      if (credits_info.find(client_id)!= credits_info.end()) {
          int credit_score = credits_info[client_id];
          auto all_candidats = clients_info.find(credit_score) ;
          if (all_candidats != clients_info.end()) {
              auto cand = all_candidats->second.find(client_id) ;
              if (cand != all_candidats->second.end())
                  all_candidats->second.erase(cand);
          }
          credits_info.erase(client_id);
          return true;
      }
      return false;
  }

  int Lookup(const string& client_id)  {
      if (credits_info.find(client_id)!= credits_info.end()) {
          return credits_info[client_id] + credit_offset;
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
          return *max_iter->second.begin();
      }
      else
          return "";
  }
private:
    int credit_offset = 0;
    unordered_map<string,int > credits_info; // map each client to its credits
    map<int, unordered_set<string>> clients_info ;// map each credits to  all clients that have the same credits
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
