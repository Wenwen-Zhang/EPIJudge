#include "test_framework/generic_test.h"
long long Reverse(int x) {
  long long res = 0;
  bool isNegative = false;
  if (x < 0 ){
    x = abs (x);
    isNegative = true;
  }
  while (x) {
    res = res * 10 + x % 10;
    x /=10; 
  }
  return isNegative? -res : res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_digits.cc", "reverse_digits.tsv",
                         &Reverse, DefaultComparator{}, param_names);
}
