#include <string>

#include "test_framework/generic_test.h"
using std::string;

string LookAndSay(int n) {
  string res = "1";
  for (int i = 1; i < n; ++i) {
    string tmp;
    for (int j = 0; j < res.size(); ++j) {
      int count = 1;
      while (j + 1 < res.size() && res[j] == res[j+1]) {
        ++j, ++count;
      }
      tmp += std::to_string(count) + res[j];
    }
    res = tmp;
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
