#include <stdexcept>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::length_error;
#include <stack>


class Stack {
public:
		bool Empty() const {
			return st.empty();
		}

		int Max() const {
			return max_st.top();
		}

		int Pop() {
			int top = -1;
			top = st.top();
			st.pop();
			max_st.pop();
			return top;
		}

		void Push(int x) {
			if (max_st.empty() || x > max_st.top())
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
