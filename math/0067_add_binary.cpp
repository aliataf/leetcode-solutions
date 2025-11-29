/*
 * Problem: 67. Add Binary
 * Link: https://leetcode.com/problems/add-binary/
 * Difficulty: Easy
 *
 * Description:
 * Given two binary strings a and b, return their sum as a binary string.
 *
 * Example:
 * Input: a = "11", b = "1"
 * Output: "100"
 *
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 *
 * Constraints:
 * - 1 <= a.length, b.length <= 10^4
 * - a and b consist only of '0' or '1' characters.
 * - Each string does not contain leading zeros except for the zero itself.
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  /*
   * Approach: Simulate binary addition with carry
   *
   * Strategy:
   * 1. Start from the rightmost bits of both strings
   * 2. Add corresponding bits plus any carry from previous position
   * 3. Calculate the result bit (sum % 2) and new carry (sum / 2)
   * 4. Insert the result bit at the beginning of the result string
   * 5. Continue until both strings are exhausted
   * 6. If there's a remaining carry, add it to the front
   *
   * Time Complexity: O(max(n, m)) where n and m are lengths of a and b
   * Space Complexity: O(max(n, m)) for the result string
   */
  string addBinary(string a, string b) {
    int carry = 0, n = a.size() - 1, m = b.size() - 1;
    string res = "";
    while (n >= 0 || m >= 0) {
      int bit1 = n < 0 ? 0 : (a[n] - '0');
      int bit2 = m < 0 ? 0 : (b[m] - '0');
      int sum = bit1 + bit2 + carry;
      int bit = sum % 2;
      carry = sum / 2;
      res.insert(res.begin(), bit + '0');
      n--;
      m--;
    }

    if (carry > 0) {
      res.insert(res.begin(), carry + '0');
    }

    return res;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  string a1 = "11", b1 = "1";
  string result1 = solution.addBinary(a1, b1);
  cout << "Test 1: " << result1 << " (Expected: 100)" << endl;

  // Test Case 2
  string a2 = "1010", b2 = "1011";
  string result2 = solution.addBinary(a2, b2);
  cout << "Test 2: " << result2 << " (Expected: 10101)" << endl;

  // Test Case 3
  string a3 = "0", b3 = "0";
  string result3 = solution.addBinary(a3, b3);
  cout << "Test 3: " << result3 << " (Expected: 0)" << endl;

  // Test Case 4
  string a4 = "1111", b4 = "1111";
  string result4 = solution.addBinary(a4, b4);
  cout << "Test 4: " << result4 << " (Expected: 11110)" << endl;

  return 0;
}
