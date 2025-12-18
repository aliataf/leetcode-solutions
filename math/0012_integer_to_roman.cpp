/*
 * Problem: 12. Integer to Roman
 * Link: https://leetcode.com/problems/integer-to-roman/
 * Difficulty: Medium
 *
 * Description:
 * Roman numerals are represented by seven different symbols: I, V, X, L, C, D,
 * M.
 *
 * Symbol       Value
 * I             1
 * V             5
 * X             10
 * L             50
 * C             100
 * D             500
 * M             1000
 *
 * Roman numerals are usually written largest to smallest from left to right.
 * However, there are six special subtractive cases:
 * - I before V (5) or X (10) makes 4 or 9.
 * - X before L (50) or C (100) makes 40 or 90.
 * - C before D (500) or M (1000) makes 400 or 900.
 *
 * Given an integer, convert it to a roman numeral.
 *
 * Example:
 * Input: num = 3
 * Output: "III"
 *
 * Input: num = 58
 * Output: "LVIII"
 * Explanation: L = 50, V = 5, III = 3.
 *
 * Input: num = 1994
 * Output: "MCMXCIV"
 * Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
 *
 * Constraints:
 * - 1 <= num <= 3999
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  /*
   * Approach: Greedy Subtraction
   *
   * Key Insight: Process the number from largest to smallest value. At each
   * step, subtract the largest possible Roman numeral value and append the
   * corresponding symbol. This handles both regular values and the special
   * subtractive cases.
   *
   * Strategy:
   * 1. Check values in descending order (1000, 900, 500, 400, 100, 90, 50, 40,
   * 10, 9, 5, 4, 1)
   * 2. For each value, if num >= value:
   *    - Append the corresponding Roman symbol(s) to result
   *    - Subtract the value from num
   * 3. Repeat until num becomes 0
   *
   * Why greedy works: Roman numerals are designed so that the greedy approach
   * always produces the correct (and shortest) representation.
   *
   * Time Complexity: O(1) - bounded by max value 3999, at most ~15 iterations
   * Space Complexity: O(1) - result string length is bounded
   */
  string intToRoman(int num) {
    string res = "";
    while (num > 0) {
      if (num >= 1000) {
        res += "M";
        num -= 1000;
      } else if (num >= 900) {
        res += "CM";
        num -= 900;
      } else if (num >= 500) {
        res += "D";
        num -= 500;
      } else if (num >= 400) {
        res += "CD";
        num -= 400;
      } else if (num >= 100) {
        res += "C";
        num -= 100;
      } else if (num >= 90) {
        res += "XC";
        num -= 90;
      } else if (num >= 50) {
        res += "L";
        num -= 50;
      } else if (num >= 40) {
        res += "XL";
        num -= 40;
      } else if (num >= 10) {
        res += "X";
        num -= 10;
      } else if (num >= 9) {
        res += "IX";
        num -= 9;
      } else if (num >= 5) {
        res += "V";
        num -= 5;
      } else if (num >= 4) {
        res += "IV";
        num -= 4;
      } else if (num >= 1) {
        res += "I";
        num -= 1;
      }
    }

    return res;
  }
};

// ============== Test Cases ==============
void runTest(int num, string expected) {
  Solution solution;
  string result = solution.intToRoman(num);
  cout << "num: " << num << " -> \"" << result << "\""
       << (result == expected ? " [PASSED]" : " [FAILED]") << endl;
}

int main() {
  runTest(3, "III");
  runTest(58, "LVIII");
  runTest(1994, "MCMXCIV");
  runTest(4, "IV");
  runTest(9, "IX");
  runTest(40, "XL");
  runTest(90, "XC");
  runTest(400, "CD");
  runTest(900, "CM");
  runTest(3999, "MMMCMXCIX");

  return 0;
}
