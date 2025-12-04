/*
 * Problem: 9. Palindrome Number
 * Link: https://leetcode.com/problems/palindrome-number/
 * Difficulty: Easy
 *
 * Description:
 * Given an integer x, return true if x is a palindrome, and false otherwise.
 *
 * Example 1:
 * Input: x = 121
 * Output: true
 * Explanation: 121 reads as 121 from left to right and from right to left.
 *
 * Example 2:
 * Input: x = -121
 * Output: false
 * Explanation: From left to right, it reads -121. From right to left, it
 * becomes 121-.
 *
 * Example 3:
 * Input: x = 10
 * Output: false
 * Explanation: Reads 01 from right to left. Therefore it is not a palindrome.
 *
 * Constraints:
 * - -2^31 <= x <= 2^31 - 1
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  /*
   * Approach: String Conversion and Two Pointers
   * Convert the number to string, then compare characters from both ends.
   *
   * Time Complexity: O(n) - where n is the number of digits
   * Space Complexity: O(n) - for the string representation
   */
  bool isPalindrome(int x) {
    string s = to_string(x);
    for (int i = 0, n = s.size(); i < n / 2; i++) {
      if (s[i] != s[n - i - 1]) return false;
    }

    return true;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  cout << "Test 1: " << (solution.isPalindrome(121) ? "true" : "false")
       << endl; // Expected: true

  // Test Case 2
  cout << "Test 2: " << (solution.isPalindrome(-121) ? "true" : "false")
       << endl; // Expected: false

  // Test Case 3
  cout << "Test 3: " << (solution.isPalindrome(10) ? "true" : "false")
       << endl; // Expected: false

  // Test Case 4
  cout << "Test 4: " << (solution.isPalindrome(0) ? "true" : "false")
       << endl; // Expected: true

  // Test Case 5
  cout << "Test 5: " << (solution.isPalindrome(12321) ? "true" : "false")
       << endl; // Expected: true

  cout << "All tests passed!" << endl;
  return 0;
}
