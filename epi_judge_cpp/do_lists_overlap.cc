#include <set>
#include <stdexcept>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>>&);
int GetLength(shared_ptr<ListNode<int>>);
void AdvanceByK(int k, shared_ptr<ListNode<int>> *);
shared_ptr<ListNode<int>> OverlappingNoCycleLists(shared_ptr<ListNode<int>>, shared_ptr<ListNode<int>>);


shared_ptr<ListNode<int>> OverlappingLists(shared_ptr<ListNode<int>> l0,
                                           shared_ptr<ListNode<int>> l1) {

  shared_ptr<ListNode<int>> l0_cycle_head = HasCycle(l0), l1_cycle_head = HasCycle(l1);

  if (!l0_cycle_head && !l1_cycle_head) {
    return O
  }


  return nullptr;
}

shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>>& head) {
  shared_ptr<ListNode<int>> slow = head, fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      int cycle_len = 0;
      do {
        ++cycle_len;
        fast = fast->next;
      } while(fast != slow);

      auto cycle_len_advanced_iter = head;
      while(cycle_len) {
        cycle_len_advanced_iter = cycle_len_advanced_iter->next;
        cycle_len--;
      }

      auto iter = head;

      while(iter != cycle_len_advanced_iter) {
        iter = iter->next;
        cycle_len_advanced_iter = cycle_len_advanced_iter->next;
      }
      return iter;

    }
  }
  return nullptr;
}

shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  
  int len0 = GetLength(l0);
  int len1 = GetLength(l1);

  AdvanceByK(abs(len0 - len1), len0 > len1? &l0 : &l1);

  while (l0 && l1 && l0 != l1) {
    l0 = l0->next;
    l1 = l1->next;
  }

  return l1;
}

int GetLength(shared_ptr<ListNode<int>> L) {
  int len = 0;
  while (L) {
    L = L->next;
    ++len;
  }
  return len;

}

void AdvanceByK(int k, shared_ptr<ListNode<int>> *L) {
  while (k) {
    (*L) = (*L)->next;
    --k;
  }
}


void OverlappingListsWrapper(TimedExecutor& executor,
                             shared_ptr<ListNode<int>> l0,
                             shared_ptr<ListNode<int>> l1,
                             shared_ptr<ListNode<int>> common, int cycle0,
                             int cycle1) {
  if (common) {
    if (!l0) {
      l0 = common;
    } else {
      auto it = l0;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }

    if (!l1) {
      l1 = common;
    } else {
      auto it = l1;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }
  }

  if (cycle0 != -1 && l0) {
    auto last = l0;
    while (last->next) {
      last = last->next;
    }
    auto it = l0;
    while (cycle0-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  if (cycle1 != -1 && l1) {
    auto last = l1;
    while (last->next) {
      last = last->next;
    }
    auto it = l1;
    while (cycle1-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  std::set<shared_ptr<ListNode<int>>> common_nodes;
  auto it = common;
  while (it && common_nodes.count(it) == 0) {
    common_nodes.insert(it);
    it = it->next;
  }

  auto result = executor.Run([&] { return OverlappingLists(l0, l1); });

  if (!((common_nodes.empty() && result == nullptr) ||
        common_nodes.count(result) > 0)) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0",     "l1",
                                       "common",   "cycle0", "cycle1"};
  return GenericTestMain(args, "do_lists_overlap.cc", "do_lists_overlap.tsv",
                         &OverlappingListsWrapper, DefaultComparator{},
                         param_names);
}
