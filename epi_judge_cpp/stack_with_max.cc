#include <stdexcept>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <algorithm>
#include <stack>
#include <stdexcept>

using std::length_error;
using std::max;
using std::stack;

class Stack {
 public:
  bool Empty() const {
    return element_.empty();
  }

  int Max() const {
    if (Empty()) {
      throw length_error("Max(): empty stack");
    }
    return cache_max_with_count_.top().max;
  }

  int Pop() {
    if (Empty()) {
      throw length_error("Pop(): empty stack");
    }
    int pop_element = element_.top();
    element_.pop();
    const int curr_max = cache_max_with_count_.top().max;
    if (pop_element == curr_max) {
      int & max_freq = cache_max_with_count_.top().count;
      --max_freq;
      if (max_freq == 0) {
        cache_max_with_count_.pop();
      }

    }

    return pop_element;
  }

  void Push(int x) {
    element_.emplace(x);
    if (cache_max_with_count_.empty()) {
      cache_max_with_count_.emplace(MaxWithCount{x, 1});
    }
    else{
      const int curr_max = cache_max_with_count_.top().max;
      if (x == curr_max) {
        int & max_freq = cache_max_with_count_.top().count;
        ++max_freq;
      }
      else if (x > curr_max) {
        cache_max_with_count_.emplace(MaxWithCount{x, 1});
      }
    }
  }


  private:
    stack<int> element_;
    struct MaxWithCount{
      int max, count;
    };
    stack<MaxWithCount> cache_max_with_count_;
};
struct StackOp {
  std::string op;
  int argument;
};

namespace test_framework {
template <>
struct SerializationTrait<StackOp> : UserSerTrait<StackOp, std::string, int> {};
}  // namespace test_framework

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
          throw TestFailure("Pop: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "max") {
        int result = s.Max();
        if (result != x.argument) {
          throw TestFailure("Max: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else if (x.op == "empty") {
        int result = s.Empty();
        if (result != x.argument) {
          throw TestFailure("Empty: expected " + std::to_string(x.argument) +
                            ", got " + std::to_string(result));
        }
      } else {
        throw std::runtime_error("Unsupported stack operation: " + x.op);
      }
    }
  } catch (length_error&) {
    throw TestFailure("Unexpected length_error exception");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "stack_with_max.cc", "stack_with_max.tsv",
                         &StackTester, DefaultComparator{}, param_names);
}
