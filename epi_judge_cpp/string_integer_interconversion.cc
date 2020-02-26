#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  // TODO - you fill in here.
  if(x == 0) return "0";
  bool is_negative = x < 0? true: false;
  string res; 

  do  {
    res += '0' + abs(x % 10);
    x /= 10;
  } while (x);

  if (is_negative) res += '-';

  string s = {res.rbegin(), res.rend()};
  return s;
}
int StringToInt(const string& s) {
  int res = 0;
  bool has_sign = false;
  if (s[0] == '-' || s[0] == '+') {
    has_sign= true;
  }
  for (int i = (has_sign? 1: 0 ); i < s.size(); ++i) {
    const int digit = s[i] - '0';
    res = res * 10 + digit;
  }
  return s[0] == '-'? -res: res;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
