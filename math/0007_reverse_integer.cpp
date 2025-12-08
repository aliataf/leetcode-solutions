/*
 * Problem: 7. Reverse Integer
 * Link: https://leetcode.com/problems/reverse-integer/
 * Difficulty: Medium
 *
 * Description:
 * Given a signed 32-bit integer x, return x with its digits reversed.
 * If reversing x causes the value to go outside the signed 32-bit integer range
 * [-2^31, 2^31 - 1], then return 0.
 * Assume the environment does not allow you to store 64-bit integers (signed or
 * unsigned).
 *
 * Example:
 * Input: x = 123
 * Output: 321
 *
 * Input: x = -123
 * Output: -321
 *
 * Input: x = 120
 * Output: 21
 *
 * Constraints:
 * - -2^31 <= x <= 2^31 - 1
 */

#include <climits>
#include <iostream>

using namespace std;

class Solution {
public:
  /*
   * Approach: Build Reversed Number with Overflow Check
   *
   * Key Insight: Before multiplying by 10, check if the result would overflow.
   * If res > INT_MAX/10, multiplying by 10 will overflow.
   * If res < INT_MIN/10, multiplying by 10 will underflow.
   *
   * Strategy:
   * Extract digits from the end using modulo and build the reversed number.
   * Check for overflow before each multiplication to avoid undefined behavior.
   *
   * Time Complexity: O(log x) - number of digits
   * Space Complexity: O(1)
   */
  int reverse(int x) {
    int res = 0;
    while (x) {
      if (res > (INT_MAX / 10) || res < (INT_MIN / 10)) return 0;
      res = res * 10 + (x % 10);
      x /= 10;
    }

    return res;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  cout << "Test 1: " << solution.reverse(123) << " (Expected: 321)" << endl;
  cout << "Test 2: " << solution.reverse(-123) << " (Expected: -321)" << endl;
  cout << "Test 3: " << solution.reverse(120) << " (Expected: 21)" << endl;
  cout << "Test 4: " << solution.reverse(1534236469) << " (Expected: 0)"
       << endl;

  return 0;
}
