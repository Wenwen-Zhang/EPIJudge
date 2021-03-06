#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if (start == finish) return L;
  shared_ptr<ListNode<int>> dummy_head = std::make_shared<ListNode<int>>(ListNode<int>{0, L});
  shared_ptr<ListNode<int>> sublist_head = dummy_head;

  int i = 1;
  while ( i < start) {
    sublist_head = sublist_head->next;
    ++i;
  }

  shared_ptr<ListNode<int>> iter = sublist_head->next;
  while (start < finish) {
    auto tmp = iter->next;
    iter->next = tmp->next;
    tmp->next = sublist_head->next;
    sublist_head->next = tmp;
    ++start;

  }
  return dummy_head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
