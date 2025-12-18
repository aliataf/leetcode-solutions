/*
 * Problem: 10. Regular Expression Matching
 * Link: https://leetcode.com/problems/regular-expression-matching/
 * Difficulty: Hard
 *
 * Description:
 * Given an input string s and a pattern p, implement regular expression
 * matching with support for '.' and '*' where:
 * '.' Matches any single character.​​​​
 * '*' Matches zero or more of the preceding element.
 * The matching should cover the entire input string (not partial).
 *
 * Example:
 * Input: s = "aa", p = "a"
 * Output: false
 *
 * Input: s = "aa", p = "a*"
 * Output: true
 *
 * Input: s = "ab", p = ".*"
 * Output: true
 *
 * Constraints:
 * - 1 <= s.length <= 20
 * - 1 <= p.length <= 20
 * - s contains only lowercase English letters.
 * - p contains only lowercase English letters, '.', and '*'.
 * - It is guaranteed for each appearance of the character '*', there will be a
 * previous valid character to match.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<vector<int>> memo;

  /*
   * Approach: Dynamic Programming (Top-Down with Memoization)
   *
   * Key Insight: The problem has optimal substructure and overlapping
   * subproblems. We can use recursion with memoization to solve it efficiently.
   *
   * Strategy:
   * 1. Base Case: If we reach the end of the pattern (j == pattern.size()),
   *    the result is true only if we also reached the end of the string (i ==
   text.size()).
   * 2. Check if the first character of the current substring matches (text[i]
   == pattern[j] or pattern[j] == '.').
   * 3. Handle the '*' wildcard (peek at p[j+1]):
   *    - Option A: Ignore the "*" and its preceding character (match zero
   occurrences).
   *    - Option B: If the first character matched, move to text[i+1] and stay
   at pattern[j].
   * 4. Handle standard matching when no '*' follows: Match the character and
   move both.

   *
   * Time Complexity: O(S * P) where S and P are lengths of string and pattern.
   * Space Complexity: O(S * P) for the memoization table.
   */
  bool isMatch(string s, string p) {
    memo.assign(s.size() + 1, vector<int>(p.size() + 1, -1));
    if (p == "") return s == "";
    return dp(0, 0, s, p);
  }

  bool dp(int i, int j, const string &text, const string &pattern) {
    if (memo[i][j] != -1) return memo[i][j];

    bool result;
    if (j == pattern.size()) {
      result = (i == text.length());
    } else {
      bool firstMatch =
          (i < text.size() && (text[i] == pattern[j] || pattern[j] == '.'));

      if (j + 1 < pattern.size() && pattern[j + 1] == '*') {
        // Case 1: Match 0 of the preceding element (jump over pattern[j]*)
        // Case 2: Match 1 or more (only if firstMatch is true, move string
        // pointer)
        result = (dp(i, j + 2, text, pattern) ||
                  (firstMatch && dp(i + 1, j, text, pattern)));
      } else {
        // Normal character match
        result = (firstMatch && dp(i + 1, j + 1, text, pattern));
      }
    }

    return memo[i][j] = result;
  }
};

// ============== Test Cases ==============
void runTest(string s, string p, bool expected) {
  Solution solution;
  bool result = solution.isMatch(s, p);
  cout << "s: \"" << s << "\", p: \"" << p << "\" -> "
       << (result ? "true" : "false")
       << (result == expected ? " [PASSED]" : " [FAILED]") << endl;
}

int main() {
  runTest("aa", "a", false);
  runTest("aa", "a*", true);
  runTest("ab", ".*", true);
  runTest("aab", "c*a*b", true);
  runTest("mississippi", "mis*is*p*.", false);
  runTest("", ".*", true);

  return 0;
}
