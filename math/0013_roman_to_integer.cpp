/*
 * Problem: 13. Roman to Integer
 * Link: https://leetcode.com/problems/roman-to-integer/
 * Difficulty: Easy
 *
 * Description:
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D
 * and M. Given a roman numeral, convert it to an integer.
 *
 * Example:
 * Input: s = "III"
 * Output: 3
 *
 * Input: s = "LVIII"
 * Output: 58
 * Explanation: L = 50, V= 5, III = 3.
 *
 * Input: s = "MCMXCIV"
 * Output: 1994
 * Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 *
 * Constraints:
 * - 1 <= s.length <= 15
 * - s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M').
 * - It is guaranteed that s is a valid roman numeral in the range [1, 3999].
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  /*
   * Approach: Iterative check with lookahead
   * Iterate through the string. For each character, check if it forms a
   * subtractive pair with the next character (e.g., IV, IX). If so, add the
   * combined value and skip the next char. Otherwise, add the value of the
   * single character.
   *
   * Time Complexity: O(n) where n is the length of the string
   * Space Complexity: O(1)
   */
  int romanToInt(string s) {
    int total = 0;
    for (int i = 0; i < s.length(); i++) {
      if (i < s.length() - 1) {
        int inc = 0;
        if (s[i] == 'I' && s[i + 1] == 'V') inc = 4;
        else if (s[i] == 'I' && s[i + 1] == 'X') inc = 9;
        else if (s[i] == 'X' && s[i + 1] == 'L') inc = 40;
        else if (s[i] == 'X' && s[i + 1] == 'C') inc = 90;
        else if (s[i] == 'C' && s[i + 1] == 'D') inc = 400;
        else if (s[i] == 'C' && s[i + 1] == 'M') inc = 900;

        if (inc > 0) {
          total += inc;
          i++;
          continue;
        }
      }
      if (s[i] == 'I') total += 1;
      else if (s[i] == 'V') total += 5;
      else if (s[i] == 'X') total += 10;
      else if (s[i] == 'L') total += 50;
      else if (s[i] == 'C') total += 100;
      else if (s[i] == 'D') total += 500;
      else if (s[i] == 'M') total += 1000;
    }

    return total;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  string s1 = "III";
  int result1 = solution.romanToInt(s1);
  cout << "Test 1 (III): " << result1 << " (Expected: 3)" << endl;

  // Test Case 2
  string s2 = "LVIII";
  int result2 = solution.romanToInt(s2);
  cout << "Test 2 (LVIII): " << result2 << " (Expected: 58)" << endl;

  // Test Case 3
  string s3 = "MCMXCIV";
  int result3 = solution.romanToInt(s3);
  cout << "Test 3 (MCMXCIV): " << result3 << " (Expected: 1994)" << endl;

  return 0;
}
