#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
int RomanToInteger(const string& s) {
  std::unordered_map<char,int> m = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
  int res = m[s.back()];
  for (int i = s.size() - 2; i >= 0; --i) {
    if (m[s[i]] < m[s[i + 1]]) {
      res -= m[s[i]];
    }
    else {
      res += m[s[i]];
    }
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "roman_to_integer.cc", "roman_to_integer.tsv",
                         &RomanToInteger, DefaultComparator{}, param_names);
}
