#include <stdexcept>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::length_error;
#include <stack>

// not efficient
#if 0
class Stack {
 public:
  bool Empty() const {
    // Implement this placeholder.
    return st.empty();
  }

  int Max() const {
    // Implement this placeholder.
    return st[max_index];
  }

  int Pop() {
    // Implement this placeholder.
	  int top = -1;
	  top = st.back();
	  if (st.size()==1) {
		  max_index = -1;
		  st.pop_back();
	  }
	  else  {
		  st.pop_back();
		  int max = INT_MIN;
		  for (int i=0; i< st.size();i++) {
			  if (st[i] > max) {
				  max = st[i];
				  max_index = i;
			  }
		  }
	  }
	  return top;
  }

  void Push(int x) {
    // Implement this placeholder.
	  if (st.empty())
		  max_index = 0;
	  else if (x > st[max_index]) {
		   max_index = st.size();
	  }
	  st.push_back(x);
    return;
  }
private:
		std::vector<int> st;
		int max_index = -1;
};
#endif


class Stack {
public:
		bool Empty() const {
			// Implement this placeholder.
			return st.empty();
		}

		int Max() const {
			// Implement this placeholder.
			return max_st.top();
		}

		int Pop() {
			// Implement this placeholder.
			int top = -1;
			top = st.top();
			st.pop();
			max_st.pop();
			return top;
		}

		void Push(int x) {
			// Implement this placeholder.
			if (x > max_st.top())
				max_st.push(x);
			else
				max_st.push(max_st.top());
			st.push(x);
		}
private:
		std::stack<int> st;
		std::stack<int> max_st;
};

struct StackOp {
  std::string op;
  int argument;
};

template <>
struct SerializationTraits<StackOp> : UserSerTraits<StackOp, std::string, int> {
};

void StackTester(const std::vector<StackOp>& ops) {
  try {
    Stack s;
    for (auto& x : ops) {
      if (x.op == "Stack") {
        continue;
      } else if (x.op == "push") {
        s.Push(x.argument);
      } else if (x.op == "pop") {
        int result = s.Pop();
        if (result != x.argument) {
          throw TestFailureException("Pop: expected " +
                                     std::to_string(x.argument) + ", got " +
                                     std::to_string(result));
        }
      } else if (x.op == "max") {
        int result = s.Max();
        if (result != x.argument) {
          throw TestFailureException("Max: expected " +
                                     std::to_string(x.argument) + ", got " +
                                     std::to_string(result));
        }
      } else if (x.op == "empty") {
        int result = s.Empty();
        if (result != x.argument) {
          throw TestFailureException("Empty: expected " +
                                     std::to_string(x.argument) + ", got " +
                                     std::to_string(result));
        }
      } else {
        throw std::runtime_error("Unsupported stack operation: " + x.op);
      }
    }
  } catch (length_error&) {
    throw TestFailureException("Unexpected length_error exception");
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"ops"};
  generic_test_main(argc, argv, param_names, "stack_with_max.tsv",
                    &StackTester);
  return 0;
}
