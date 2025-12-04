/*
 * Problem: 121. Best Time to Buy and Sell Stock
 * Link: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * Difficulty: Easy
 *
 * Description:
 * You are given an array prices where prices[i] is the price of a given stock
 * on the ith day. You want to maximize your profit by choosing a single day to
 * buy one stock and choosing a different day in the future to sell that stock.
 * Return the maximum profit you can achieve from this transaction. If you
 * cannot achieve any profit, return 0.
 *
 * Example:
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit =
 * 6-1 = 5.
 *
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transactions are done and the max profit = 0.
 *
 * Constraints:
 * - 1 <= prices.length <= 10^5
 * - 0 <= prices[i] <= 10^4
 */

#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: One Pass with Min Tracking
   *
   * Strategy:
   * 1. Track the minimum price seen so far.
   * 2. For each price, calculate the profit if we sell at this price (price -
   * min).
   * 3. Update the maximum profit if the current profit is higher.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(1)
   */
  int maxProfit(vector<int> &prices) {
    int mn = INT_MAX, res = 0;
    for (int price : prices) {
      mn = min(mn, price);
      res = max(res, price - mn);
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
  cout << "Test 1: " << result1 << " (Expected: 5)" << endl;

  // Test Case 2
  vector<int> prices2 = {7, 6, 4, 3, 1};
  int result2 = solution.maxProfit(prices2);
  cout << "Test 2: " << result2 << " (Expected: 0)" << endl;

  // Test Case 3
  vector<int> prices3 = {2, 4, 1};
  int result3 = solution.maxProfit(prices3);
  cout << "Test 3: " << result3 << " (Expected: 2)" << endl;

  return 0;
}
