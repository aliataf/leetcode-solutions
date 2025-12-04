/*
 * Problem: 69. Sqrt(x)
 * Link: https://leetcode.com/problems/sqrtx/
 * Difficulty: Easy
 *
 * Description:
 * Given a non-negative integer x, return the square root of x rounded down to
 * the nearest integer. The returned integer should be non-negative as well. You
 * must not use any built-in exponent function or operator.
 *
 * Example:
 * Input: x = 4
 * Output: 2
 * Explanation: The square root of 4 is 2, so we return 2.
 *
 * Input: x = 8
 * Output: 2
 * Explanation: The square root of 8 is 2.82842..., and since we round it down
 * to the nearest integer, 2 is returned.
 *
 * Constraints:
 * - 0 <= x <= 2^31 - 1
 */

#include <iostream>

using namespace std;

class Solution {
public:
  /*
   * Approach: Linear Search
   *
   * Strategy:
   * 1. Handle base cases: if x is 0 or 1, return x.
   * 2. Iterate starting from i = 1.
   * 3. Check if i * i is equal to x. If so, return i.
   * 4. Check if i * i is greater than x. If so, the floor sqrt is i - 1.
   * 5. Use 'long' for the loop variable to prevent overflow during
   * multiplication.
   *
   * Time Complexity: O(sqrt(x))
   * Space Complexity: O(1)
   */
  int mySqrt(int x) {
    if (x <= 1) return x;
    long i;
    for (i = 1; i * i <= x; i++) {
      if (i * i == x) return i;
    }
    return i - 1;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  int x1 = 4;
  int result1 = solution.mySqrt(x1);
  cout << "Test 1: " << result1 << " (Expected: 2)" << endl;

  // Test Case 2
  int x2 = 8;
  int result2 = solution.mySqrt(x2);
  cout << "Test 2: " << result2 << " (Expected: 2)" << endl;

  // Test Case 3
  int x3 = 0;
  int result3 = solution.mySqrt(x3);
  cout << "Test 3: " << result3 << " (Expected: 0)" << endl;

  // Test Case 4
  int x4 = 1;
  int result4 = solution.mySqrt(x4);
  cout << "Test 4: " << result4 << " (Expected: 1)" << endl;

  return 0;
}
