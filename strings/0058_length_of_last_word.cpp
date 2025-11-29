/*
 * Problem: 58. Length of Last Word
 * Link: https://leetcode.com/problems/length-of-last-word/
 * Difficulty: Easy
 *
 * Description:
 * Given a string s consisting of words and spaces, return the length of the
 * last word in the string. A word is a maximal substring consisting of
 * non-space characters only.
 *
 * Example:
 * Input: s = "Hello World"
 * Output: 5
 * Explanation: The last word is "World" with length 5.
 *
 * Input: s = "   fly me   to   the moon  "
 * Output: 4
 * Explanation: The last word is "moon" with length 4.
 *
 * Input: s = "luffy is still joyboy"
 * Output: 6
 * Explanation: The last word is "joyboy" with length 6.
 *
 * Constraints:
 * - 1 <= s.length <= 10^4
 * - s consists of only English letters and spaces ' '.
 * - There will be at least one word in s.
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  /*
   * Approach: String trimming and substring extraction
   *
   * Strategy:
   * 1. Trim trailing spaces from the end
   * 2. Trim leading spaces from the beginning
   * 3. Find the last space in the trimmed string
   * 4. Extract the substring after the last space (or entire string if no
   * space)
   * 5. Return the length of this substring
   *
   * Time Complexity: O(n) where n is the length of the string
   * Space Complexity: O(n) for the substring creation
   */
  int lengthOfLastWord(string s) {
    s.erase(s.find_last_not_of(' ') + 1);
    s.erase(0, s.find_first_not_of(' '));
    size_t pos = s.find_last_of(' ');
    string last = pos != string::npos ? s.substr(pos + 1) : s;
    return last.length();
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  string s1 = "Hello World";
  int result1 = solution.lengthOfLastWord(s1);
  cout << "Test 1: " << result1 << " (Expected: 5)" << endl;

  // Test Case 2
  string s2 = "   fly me   to   the moon  ";
  int result2 = solution.lengthOfLastWord(s2);
  cout << "Test 2: " << result2 << " (Expected: 4)" << endl;

  // Test Case 3
  string s3 = "luffy is still joyboy";
  int result3 = solution.lengthOfLastWord(s3);
  cout << "Test 3: " << result3 << " (Expected: 6)" << endl;

  // Test Case 4
  string s4 = "a";
  int result4 = solution.lengthOfLastWord(s4);
  cout << "Test 4: " << result4 << " (Expected: 1)" << endl;

  return 0;
}
