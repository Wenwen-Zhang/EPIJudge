#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
  double max_profit = 0;
  // double min_price_so_far = std::numeric_limits<double>::max();
  // vector<double> first_profit (prices.size(), 0);

  // for (int i = 0; i < prices.size(); ++i) {
  //   min_price_so_far = std::min(prices[i], min_price_so_far);
  //   max_profit = std::max(max_profit, prices[i] - min_price_so_far);
  //   first_profit[i] = max_profit;

  // }

  // double max_price_so_far = std::numeric_limits<double>::min();
  // for (int i = prices.size() - 1; i > 0; --i) {
  //   max_price_so_far = std::max(max_price_so_far, prices[i]);
  //   max_profit = std::max(max_profit, max_price_so_far - prices[i] + first_profit[i - 1]);
  // }

  double max_price = std::numeric_limits<double>::min();
  double min_price = std::numeric_limits<double>::max();
  int i = 0;
  const int length = prices.size(); 
  while (i < length - 1) {
    while ( i < length - 1 && prices[i] >= prices[i + 1] ){
      i++;
    }
    min_price = prices[i];
    while ( i < length - 1 && prices[i] <= prices[i + 1]) {
      i++;
    }
    max_price = prices[i];
    max_profit += max_price - min_price;
  }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
