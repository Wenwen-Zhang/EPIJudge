#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double min_price_so_far = std::numeric_limits<double>::max();
  double max_profit = 0;
  for (const double & price: prices) {
    max_profit = std::max(max_profit, price - min_price_so_far);
    min_price_so_far = std::min(min_price_so_far, price);
  }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
