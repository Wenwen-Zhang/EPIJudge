#include "test_framework/generic_test.h"
#include <iostream>


unsigned long long ReverseBits(unsigned long long n) {

  // n = ((n & 0xffffffff00000000) >> 32) | ((n & 0x00000000ffffffff )<< 32);
  // n = ((n & 0xffff0000ffff0000) >> 16) | ((n & 0x0000ffff0000ffff) << 16);
  // n = ((n & 0xff00ff00ff00ff00) >> 8) | ((n & 0x00ff00ff00ff00ff) << 8);
  // n = ((n & 0xf0f0f0f0f0f0f0f0) >> 4) | ((n & 0x0f0f0f0f0f0f0f0f) << 4);
  // n = ((n & 0xcccccccccccccccc) >> 2) | ((n & 0x3333333333333333) << 2);
  // n = ((n & 0xaaaaaaaaaaaaaaaa) >> 1) | ((n & 0x5555555555555555) << 1);

  // return n;

  unsigned long long res  = 0;

  for (int i = 0; i < 64; i++, n>>=1) {
    res <<= 1; 
    res |= n & 1;
  }

  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x"};
  return GenericTestMain(args, "reverse_bits.cc", "reverse_bits.tsv",
                         &ReverseBits, DefaultComparator{}, param_names);
}
