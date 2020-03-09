#include <string>
#include <stack>
#include <iostream>
// #include <sstream>

#include "test_framework/generic_test.h"


using std::string;
using std::stack;
using std::stringstream;
int Evaluate(const string& expression) {
  stack<int> intermediate_results;
  stringstream ss(expression);
  string token;
  const char delimiter = ',';

  while (getline(ss, token, delimiter)) {
    if ((token == "+") || (token == "-") || (token == "*") || (token == "/")){
      
    }
  }
  return 0;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
