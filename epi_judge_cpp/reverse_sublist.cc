#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if (start == finish) return L;

  shared_ptr<ListNode<int>> dummy = std::make_shared<ListNode<int>> (ListNode<int>{0, L});
  shared_ptr<ListNode<int>> sublist_dummy = dummy;

  int i = 1;

  while (i < start) {
    sublist_dummy = sublist_dummy->next;
    ++i;
  }

  shared_ptr<ListNode<int>> sublist_iter = sublist_dummy->next;
  while (start < finish) {
    auto tmp = sublist_iter->next;
    sublist_iter->next = tmp->next;
    tmp->next = sublist_dummy->next;
    sublist_dummy->next = tmp;
    ++start;
  }

  return dummy->next;


  return nullptr;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
