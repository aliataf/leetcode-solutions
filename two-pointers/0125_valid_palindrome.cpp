/*
 * Problem: 125. Valid Palindrome
 * Link: https://leetcode.com/problems/valid-palindrome/
 * Difficulty: Easy
 *
 * Description:
 * A phrase is a palindrome if, after converting all uppercase letters into
 * lowercase letters and removing all non-alphanumeric characters, it reads the
 * same forward and backward. Alphanumeric characters include letters and
 * numbers. Given a string s, return true if it is a palindrome, or false
 * otherwise.
 *
 * Example:
 * Input: s = "A man, a plan, a canal: Panama"
 * Output: true
 * Explanation: "amanaplanacanalpanama" is a palindrome.
 *
 * Input: s = "race a car"
 * Output: false
 *
 * Constraints:
 * - 1 <= s.length <= 2 * 10^5
 * - s consists only of printable ASCII characters.
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  /*
   * Approach: Two Pointers
   *
   * Strategy:
   * 1. Use two pointers, one at the start and one at the end.
   * 2. Skip non-alphanumeric characters from both ends.
   * 3. Compare characters (case-insensitive) and move pointers inward.
   * 4. If any mismatch is found, return false.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(1)
   */
  bool isPalindrome(string s) {
    int i = 0, j = s.length() - 1;
    bool res = true;
    while (i < j) {
      if (!isalnum(s[i])) {
        i++;
        continue;
      }

      if (!isalnum(s[j])) {
        j--;
        continue;
      }

      if (tolower(s[i]) != tolower(s[j])) {
        res = false;
        break;
      }

      i++;
      j--;
    }

    return res;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  cout << "Test 1: "
       << (solution.isPalindrome("A man, a plan, a canal: Panama") ? "true"
                                                                   : "false")
       << " (Expected: true)" << endl;

  // Test Case 2
  cout << "Test 2: " << (solution.isPalindrome("race a car") ? "true" : "false")
       << " (Expected: false)" << endl;

  // Test Case 3
  cout << "Test 3: " << (solution.isPalindrome(" ") ? "true" : "false")
       << " (Expected: true)" << endl;

  return 0;
}
