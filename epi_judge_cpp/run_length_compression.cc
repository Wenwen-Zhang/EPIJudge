#include <string>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;
string Decoding(const string &s) {
  string decoded;
  int cnt = 0;
  for (const char c : s) {
    if (std::isdigit(c)) {
      cnt = cnt * 10 + c - '0';
    }
    else{
      decoded.append(cnt, c);
      cnt = 0;
    }
  }
  return decoded;
}
string Encoding(const string &s) {
  string encoded;
  for (int i = 1, cnt = 1; i <= s.size(); ++i) {
    if (i == s.size() || s[i] != s[i - 1]) {
      encoded += std::to_string(cnt) + s[i - 1];
      cnt = 1;
    }
    else {
      ++cnt;
    }
  }
  return encoded;
}
void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
