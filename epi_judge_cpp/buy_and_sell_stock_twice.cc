#include <vector>

using std::vector;

double BuyAndSellStockTwice(const vector<double>& prices) {
  // Implement this placeholder.
  return 0.0;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  generic_test_main(argc, argv, "buy_and_sell_stock_twice.tsv",
                    &BuyAndSellStockTwice);
  return 0;
}
