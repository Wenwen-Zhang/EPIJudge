#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> Multiply(vector<int> num1, vector<int> num2) {
  
  
  const int sign = (num1[0] < 0) ^ (num2[0] < 0)? -1 : 1;
  num1.front() = abs(num1.front());
  num2.front() = abs(num2.front());
  
  vector<int> res (num1.size()+ num2.size(), 0);

  for (int i = num1.size() - 1; i >= 0; --i) {
    for (int j = num2.size() -1; j >= 0; --j) {
      res[i+j+1] += num1[i] * num2[j];
      res[i+j] += res[i+j+1] / 10;
      res[i+j+1] = res[i+j+1] % 10;
    }
  }

  vector<int>::iterator it = std::find_if_not(res.begin(), res.end(), [](int a) {return a == 0;});

  res = {it, res.end()};
  if (res.empty()) return {0};
  res.front() *= sign;
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num1", "num2"};
  return GenericTestMain(args, "int_as_array_multiply.cc",
                         "int_as_array_multiply.tsv", &Multiply,
                         DefaultComparator{}, param_names);
}
