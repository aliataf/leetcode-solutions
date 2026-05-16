/*
 * Problem: 29. Divide Two Integers
 * Link: https://leetcode.com/problems/divide-two-integers/
 * Difficulty: Medium
 *
 * Description:
 * Given two integers dividend and divisor, divide two integers without using
 * multiplication, division, and mod operator.
 *
 * The integer division should truncate toward zero, which means losing its
 * fractional part. For example, 8.345 would be truncated to 8, and -2.7335
 * would be truncated to -2.
 *
 * Return the quotient after dividing dividend by divisor.
 *
 * Note: Assume we are dealing with an environment that could only store
 * integers within the 32-bit signed integer range: [-2^31, 2^31 - 1]. For this
 * problem, if the quotient is strictly greater than 2^31 - 1, then return
 * 2^31 - 1, and if the quotient is strictly less than -2^31, then return
 * -2^31.
 *
 * Example 1:
 * Input: dividend = 10, divisor = 3
 * Output: 3
 *
 * Example 2:
 * Input: dividend = 7, divisor = -3
 * Output: -2
 *
 * Constraints:
 * - -2^31 <= dividend, divisor <= 2^31 - 1
 * - divisor != 0
 */

#include <climits>
#include <cstdlib>
#include <iostream>

using namespace std;

typedef long long int lli;

class Solution {
public:
  /*
   * Approach: Repeated Subtraction with Overflow Guards
   *
   * Key Insight: Division can be computed by counting how many times we can
   * subtract the divisor from the dividend before the dividend goes negative.
   * Promoting to long long lets us safely take absolute values (since
   * |INT_MIN| > INT_MAX) and handle the sign at the end.
   *
   * Strategy:
   * 1. Short-circuit the overflow / fast-path cases involving INT_MIN and
   *    INT_MAX with divisor = +/-1.
   * 2. Determine the sign of the result from the signs of dividend and divisor.
   * 3. Work with the absolute values as long long.
   * 4. Subtract divisor from dividend until it goes negative; track how many
   *    subtractions were valid (start result at -1 to discount the final
   *    over-subtraction that flips the sign).
   * 5. Re-apply the sign to the result.
   *
   * Time Complexity: O(|dividend| / |divisor|) - linear in the quotient.
   * Space Complexity: O(1).
   */
  int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;
    if (dividend == INT_MIN && divisor == 1) return INT_MIN;
    if (dividend == INT_MAX && divisor == -1) return -INT_MAX;
    if (dividend == INT_MAX && divisor == 1) return INT_MAX;

    bool negative = (dividend < 0) != (divisor < 0);
    lli result = -1;
    lli a = llabs((lli)dividend);
    lli b = llabs((lli)divisor);

    while (a >= 0) {
      a -= b;
      result++;
    }

    return negative ? -result : result;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  cout << "Test 1: " << solution.divide(10, 3) << " (Expected: 3)" << endl;
  cout << "Test 2: " << solution.divide(7, -3) << " (Expected: -2)" << endl;
  cout << "Test 3: " << solution.divide(0, 1) << " (Expected: 0)" << endl;
  cout << "Test 4: " << solution.divide(1, 1) << " (Expected: 1)" << endl;
  cout << "Test 5: " << solution.divide(-2147483648, -1)
       << " (Expected: 2147483647)" << endl;
  cout << "Test 6: " << solution.divide(-2147483648, 1)
       << " (Expected: -2147483648)" << endl;
  cout << "Test 7: " << solution.divide(-7, 2) << " (Expected: -3)" << endl;
  cout << "Test 8: " << solution.divide(-7, -2) << " (Expected: 3)" << endl;

  return 0;
}
