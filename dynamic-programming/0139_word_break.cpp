/*
 * Problem: 139. Word Break
 * Link: https://leetcode.com/problems/word-break/
 * Difficulty: Medium
 *
 * Description:
 * Given a string s and a dictionary of strings wordDict, return true if s can
 * be segmented into a space-separated sequence of one or more dictionary words.
 * Note that the same word in the dictionary may be reused multiple times.
 *
 * Example:
 * Input: s = "leetcode", wordDict = ["leet","code"]
 * Output: true
 * Explanation: Return true because "leetcode" can be segmented as "leet code".
 *
 * Input: s = "applepenapple", wordDict = ["apple","pen"]
 * Output: true
 *
 * Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
 * Output: false
 *
 * Constraints:
 * - 1 <= s.length <= 300
 * - 1 <= wordDict.length <= 1000
 * - 1 <= wordDict[i].length <= 20
 * - s and wordDict[i] consist of only lowercase English letters.
 * - All the strings of wordDict are unique.
 */

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Dynamic Programming
   *
   * Key Insight: If we can break s[0..j-1] into valid words, and s[j..i-1] is
   * also a valid word, then we can break s[0..i-1] into valid words.
   *
   * Strategy:
   * Build up the solution by checking if each prefix of the string can be
   * segmented. For each position i, we try all possible "last words" ending
   * at position i. If the substring before that last word is already
   * segmentable (dp[j] = true) and the last word itself is in the dictionary,
   * then s[0..i-1] is also segmentable.
   *
   * Time Complexity: O(n^2 * m) where n = s.length, m = avg word length
   * Space Complexity: O(n + k) where k = total chars in wordDict
   */
  bool wordBreak(string s, vector<string> &wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;

    for (int i = 1; i <= s.size(); i++) {
      for (int j = 0; j < i; j++) {
        if (dp[j] && dict.count(s.substr(j, i - j))) {
          dp[i] = true;
          break;
        }
      }
    }

    return dp[s.size()];
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  string s1 = "leetcode";
  vector<string> wordDict1 = {"leet", "code"};
  cout << "Test 1: " << (solution.wordBreak(s1, wordDict1) ? "true" : "false")
       << " (Expected: true)" << endl;

  // Test Case 2
  string s2 = "applepenapple";
  vector<string> wordDict2 = {"apple", "pen"};
  cout << "Test 2: " << (solution.wordBreak(s2, wordDict2) ? "true" : "false")
       << " (Expected: true)" << endl;

  // Test Case 3
  string s3 = "catsandog";
  vector<string> wordDict3 = {"cats", "dog", "sand", "and", "cat"};
  cout << "Test 3: " << (solution.wordBreak(s3, wordDict3) ? "true" : "false")
       << " (Expected: false)" << endl;

  return 0;
}
