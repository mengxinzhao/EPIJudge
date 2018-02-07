
#include "test_framework/test_failure_exception.h"
#include "test_framework/test_utils_serialization_traits.h"
#include <vector>
#include <algorithm>

void print(vector<int> A) {
	for (int i=0;i< A.size();i++)
		std::cout<<A[i]<<" ";
	return ;
}


class Queue {
 public:
  Queue(size_t capacity) {
	  if (capacity <=0) {
		  std::cout<<"capacity is 0 !!!" << std::endl;
		  capacity = 1;
	  }
	  std::cout<<"capacity: " << capacity<< std::endl;
	  storage.resize(capacity); // use resize not reserve.
	  head = 0;
	  tail = 0;
	  cap = capacity;

  }

  void Enqueue(int x) {
    // Implement this placeholder.
	  if ((head+1)%cap == tail) {
		  //print(storage);
		  storage.resize(cap * 2);
		  // insert slot in between head and tail
		  // tail a d head  0 0 0 0
		  // tail a d head  0  0 0 0
		  // don't need to worry about anything head goes on by +1
			// but if head rewinds..
		  if (head < tail)
		  {
			  //head rewind
			  // d a head tail b  0 0 0 0 0
			  // d a head 0 0 0 0 0 tail b
				for (int i = tail; i< cap; i++)
			    std::swap(storage[i ], storage[(i+ cap)%storage.size()]);
			  tail = (tail + cap) % storage.size();

		  }
		  cap = cap * 2;
	  }
	  storage[head] = x;
	  head = (head+1)%cap;
    return;
  }

  int Dequeue() {
    // Implement this placeholder.
	  int curr = storage[tail];
	  tail = (tail+1)%cap;
    return curr;
  }

  int Size() const {
    // Implement this placeholder.
	  if (head < tail)
		  return (cap + head- tail); // rewinded
	  else
	    return head - tail;
  }

private:
		std::vector<int> storage;
		int head;
		int tail;
		int cap;
};

struct QueueOp {
  enum { CONSTRUCT, DEQUEUE, ENQUEUE, SIZE } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = CONSTRUCT;
    } else if (op_string == "dequeue") {
      op = DEQUEUE;
    } else if (op_string == "enqueue") {
      op = ENQUEUE;
    } else if (op_string == "size") {
      op = SIZE;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case CONSTRUCT:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case DEQUEUE: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailureException("Dequeue: expected " +
                                     std::to_string(argument) + ", got " +
                                     std::to_string(result));
        }
      } break;
      case ENQUEUE:
        q.Enqueue(argument);
        break;
      case SIZE: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailureException("Size: expected " +
                                     std::to_string(argument) + ", got " +
                                     std::to_string(s));
        }
      } break;
    }
  }
};

template <>
struct SerializationTraits<QueueOp> : UserSerTraits<QueueOp, std::string, int> {
};

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"ops"};
  generic_test_main(argc, argv, param_names, "circular_queue.tsv",
                    &QueueTester);
  return 0;
}
