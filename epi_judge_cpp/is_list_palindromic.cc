#include "list_node.h"
#include "test_framework/generic_test.h"
#include <memory>

using std::shared_ptr;

// shared_ptr<ListNode<int>> ReverseList(shared_ptr<ListNode<int>> &);

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>>& L) {
  if (L == nullptr) return true;

  //   shared_ptr<ListNode<int>> slow = L, fast = L;
  // while (fast && fast->next) {
  //   fast = fast->next->next, slow = slow->next;
  // }

  // // Compares the first half and the reversed second half lists.
  // auto first_half_iter = L;

  // shared_ptr<ListNode<int>> prev = nullptr, curr = slow;

  // while (curr) {
  //   auto temp = curr->next;
  //   curr->next = prev;
  //   prev = curr;
  //   curr = temp;
  // }
  // auto second_half_iter = prev;
  
  // //  second_half_iter = ReverseList(slow);
  // while (second_half_iter && first_half_iter) {
  //   if (second_half_iter->data != first_half_iter->data) {
  //     return false;
  //   }
  //   second_half_iter = second_half_iter->next;
  //   first_half_iter = first_half_iter->next;
  // }
  // return true;

  shared_ptr<ListNode<int>> slow = L, fast = L;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }
  
  
  auto first_half_iter = L;
  shared_ptr<ListNode<int>> prev = nullptr, curr = slow;

  while (curr) {
    auto temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
  }
  auto second_half_iter = prev;

  while (first_half_iter && second_half_iter) {
    if (first_half_iter->data != second_half_iter->data) return false;
    first_half_iter = first_half_iter->next;
    second_half_iter = second_half_iter->next;
  }
  return true;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
