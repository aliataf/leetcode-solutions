/*
 * Problem: 76. Minimum Window Substring
 * Link: https://leetcode.com/problems/minimum-window-substring/
 * Difficulty: Hard
 *
 * Description:
 * Given two strings s and t of lengths m and n respectively, return the minimum
 * window substring of s such that every character in t (including duplicates)
 * is included in the window. If there is no such substring, return the empty
 * string "". The testcases will be generated such that the answer is unique.
 *
 * Example:
 * Input: s = "ADOBECODEBANC", t = "ABC"
 * Output: "BANC"
 * Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C'
 * from string t.
 *
 * Input: s = "a", t = "a"
 * Output: "a"
 *
 * Input: s = "a", t = "aa"
 * Output: ""
 * Explanation: Both 'a's from t must be included in the window.
 * Since the largest window of s only has one 'a', return empty string.
 *
 * Constraints:
 * - m == s.length
 * - n == t.length
 * - 1 <= m, n <= 10^5
 * - s and t consist of uppercase and lowercase English letters.
 */

#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Sliding Window
   *
   * Strategy:
   * 1. Use a frequency map (vector of size 128) to store counts of characters
   * in t.
   * 2. Use two pointers, 'begin' and 'end', to define a window [begin, end).
   * 3. Expand the window by moving 'end' forward:
   *    - Decrement count in map for s[end].
   *    - If count was > 0, it means s[end] is a necessary character, so
   * decrement 'counter'.
   * 4. When 'counter' becomes 0 (all characters from t are found):
   *    - Try to shrink the window from the left by moving 'begin' forward.
   *    - Update minimum window size 'd' and start position 'head' if current
   * window is smaller.
   *    - Increment count in map for s[begin].
   *    - If count becomes > 0, it means a necessary character is removed, so
   * increment 'counter'.
   * 5. Repeat until 'end' reaches the end of s.
   *
   * Time Complexity: O(m + n)
   * Space Complexity: O(1) (since map size is fixed at 128)
   */
  string minWindow(string s, string t) {
    vector<int> map(128, 0);
    for (auto c : t) {
      map[c]++;
    }
    int counter = t.size(), begin = 0, end = 0, d = INT_MAX, head = 0;
    while (end < s.size()) {
      if (map[s[end]] > 0) {
        counter--;
      }
      map[s[end]]--;
      end++;

      while (counter == 0) { // valid
        if (end - begin < d) {
          d = end - begin;
          head = begin;
        }

        map[s[begin]]++;
        if (map[s[begin]] > 0) {
          counter++; // make it invalid
        }
        begin++;
      }
    }
    return d == INT_MAX ? "" : s.substr(head, d);
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  string s1 = "ADOBECODEBANC", t1 = "ABC";
  string result1 = solution.minWindow(s1, t1);
  cout << "Test 1: \"" << result1 << "\" (Expected: \"BANC\")" << endl;

  // Test Case 2
  string s2 = "a", t2 = "a";
  string result2 = solution.minWindow(s2, t2);
  cout << "Test 2: \"" << result2 << "\" (Expected: \"a\")" << endl;

  // Test Case 3
  string s3 = "a", t3 = "aa";
  string result3 = solution.minWindow(s3, t3);
  cout << "Test 3: \"" << result3 << "\" (Expected: \"\")" << endl;

  return 0;
}
