/*
 * Problem: 8. String to Integer (atoi)
 * Link: https://leetcode.com/problems/string-to-integer-atoi/
 * Difficulty: Medium
 *
 * Description:
 * Implement the myAtoi(string s) function, which converts a string to a 32-bit
 * signed integer.
 *
 * Algorithm:
 * 1. Read in and ignore any leading whitespace.
 * 2. Check if the next character is '-' or '+'. Read this character if it is
 * either.
 * 3. Read in next characters until the next non-digit character or end of input
 * is reached.
 * 4. Convert these digits into an integer. If no digits were read, return 0.
 * 5. If the integer is out of the 32-bit signed integer range [-2^31, 2^31 -
 * 1], clamp the integer to stay in the range.
 *
 * Example:
 * Input: s = "42"
 * Output: 42
 *
 * Input: s = "   -42"
 * Output: -42
 *
 * Input: s = "4193 with words"
 * Output: 4193
 *
 * Constraints:
 * - 0 <= s.length <= 200
 * - s consists of English letters (lower-case and upper-case), digits (0-9), '
 * ', '+', '-', and '.'.
 */

#include <climits>
#include <iostream>
#include <string>

using namespace std;

typedef long long int lli;

class Solution {
public:
  /*
   * Approach: Sequential parsing with overflow detection
   *
   * Steps:
   * 1. Skip leading whitespace
   * 2. Check for optional sign ('+' or '-')
   * 3. Parse digits one by one, building the result
   * 4. Use long long to detect overflow before it happens
   * 5. Return clamped value if overflow detected
   *
   * Time Complexity: O(n) where n is the length of the string
   * Space Complexity: O(1)
   */
  int myAtoi(string s) {
    int res = 0, idx = 0, sign = 1, n = s.size();
    lli overflowCheck = 0;
    while (idx < n && s[idx] == ' ') {
      idx++;
    }
    if (idx >= n) {
      return 0;
    }
    if (s[idx] == '-' || s[idx] == '+') {
      sign = s[idx] == '-' ? -1 : 1;
      idx++;
    }
    while (idx < n) {
      int digit = s[idx] - '0';
      if (digit < 0 || digit > 9) {
        return sign * res;
      }
      overflowCheck = overflowCheck * 10 + digit;
      if (overflowCheck > INT_MAX) {
        return sign == 1 ? INT_MAX : INT_MIN;
      }
      res = (int)overflowCheck;
      idx++;
    }

    return sign * res;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  string s1 = "42";
  int result1 = solution.myAtoi(s1);
  cout << "Test 1: " << result1 << " (Expected: 42)" << endl;

  // Test Case 2
  string s2 = "   -42";
  int result2 = solution.myAtoi(s2);
  cout << "Test 2: " << result2 << " (Expected: -42)" << endl;

  // Test Case 3
  string s3 = "4193 with words";
  int result3 = solution.myAtoi(s3);
  cout << "Test 3: " << result3 << " (Expected: 4193)" << endl;

  // Test Case 4 - Overflow
  string s4 = "91283472332";
  int result4 = solution.myAtoi(s4);
  cout << "Test 4: " << result4 << " (Expected: " << INT_MAX << ")" << endl;

  return 0;
}
