#include <string>

#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
  int num = 0;
  for (int i = (num_as_string.front() == '-'? 1: 0); i < num_as_string.size(); ++i) {
    num = num * b1 + (std::isdigit(num_as_string[i])? num_as_string[i] - '0' : num_as_string[i] - 'A' + 10);
  }
  
  string numInB2 ; 

  do {
    int digit = num % b2;   
    numInB2 += static_cast<char>(digit >= 10? digit + 'A' - 10 : digit + '0');
    num /= b2;
  }while (num);
  numInB2 += (num_as_string.front() == '-'? "-":"");
  return {numInB2.rbegin(), numInB2.rend()};
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
