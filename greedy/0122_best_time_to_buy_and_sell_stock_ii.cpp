/*
 * Problem: 122. Best Time to Buy and Sell Stock II
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
 * Difficulty: Medium
 *
 * Description:
 * You are given an integer array prices where prices[i] is the price of a given
 * stock on the ith day. On each day, you may decide to buy and/or sell the
 * stock. You can only hold at most one share of the stock at any time. However,
 * you can buy it then immediately sell it on the same day. Find and return the
 * maximum profit you can achieve.
 *
 * Example:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 7
 * Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit =
 * 5-1 = 4. Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit
 * = 6-3 = 3. Total profit is 4 + 3 = 7.
 *
 * Input: prices = [1,2,3,4,5]
 * Output: 4
 * Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit =
 * 5-1 = 4. Total profit is 4.
 *
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: There is no way to make a positive profit, so we never buy the
 * stock.
 *
 * Constraints:
 * - 1 <= prices.length <= 3 * 10^4
 * - 0 <= prices[i] <= 10^4
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Greedy - Collect All Upward Slopes
   *
   * Key Insight: Since we can make unlimited transactions, we should capture
   * every profit opportunity. Any time the price goes up from one day to the
   * next, we should "buy" the previous day and "sell" the current day.
   *
   * Strategy:
   * 1. Iterate through prices starting from day 1.
   * 2. If price[i] > price[i-1], add the difference to our profit.
   * 3. This effectively captures all upward movements.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(1)
   */
  int maxProfit(vector<int> &prices) {
    int res = 0;
    for (int i = 1, n = prices.size(); i < n; i++) {
      if (prices[i] > prices[i - 1]) res += (prices[i] - prices[i - 1]);
    }

    return res;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> prices1 = {7, 1, 5, 3, 6, 4};
  int result1 = solution.maxProfit(prices1);
  cout << "Test 1: " << result1 << " (Expected: 7)" << endl;

  // Test Case 2
  vector<int> prices2 = {1, 2, 3, 4, 5};
  int result2 = solution.maxProfit(prices2);
  cout << "Test 2: " << result2 << " (Expected: 4)" << endl;

  // Test Case 3
  vector<int> prices3 = {7, 6, 4, 3, 1};
  int result3 = solution.maxProfit(prices3);
  cout << "Test 3: " << result3 << " (Expected: 0)" << endl;

  return 0;
}
