#include "test_framework/generic_test.h"
#include <iostream>
short Parity(unsigned long long x) {  
  short res = 0;
  while (x) {  
    //res ^= (x&1);
    //x >>= 1; 
    
    res ^= 1;
    x &= (x - 1); // Drop the lowest set bit of x
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "parity.cc", "parity.tsv", &Parity,
                         DefaultComparator{}, param_names);
}
