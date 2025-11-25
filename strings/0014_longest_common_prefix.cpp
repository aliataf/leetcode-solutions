/*
 * Problem: 14. Longest Common Prefix
 * Link: https://leetcode.com/problems/longest-common-prefix/
 * Difficulty: Easy
 *
 * Description:
 * Write a function to find the longest common prefix string amongst an array of
 * strings. If there is no common prefix, return an empty string "".
 *
 * Example:
 * Input: strs = ["flower","flow","flight"]
 * Output: "fl"
 *
 * Input: strs = ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 *
 * Constraints:
 * - 1 <= strs.length <= 200
 * - 0 <= strs[i].length <= 200
 * - strs[i] consists of only lowercase English letters.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Horizontal Scanning
   * Take the first string as the initial reference 'res'. Iterate through the
   * rest of the strings. For each string, compare it with 'res' character by
   * character and update 'res' to be the common substring found so far. If
   * 'res' becomes empty, stop and return "".
   *
   * Time Complexity: O(S) where S is the sum of all characters in all strings.
   * Space Complexity: O(1) ignoring the space taken by the result.
   */
  string longestCommonPrefix(vector<string> &strs) {
    string res = strs[0];
    for (int i = 1, n = strs.size(); i < n; i++) {
      int j = 0, m = min(strs[i].size(), res.size());
      for (j = 0; j < m; j++) {
        if (strs[i][j] != res[j])
          break;
      }
      res = res.substr(0, j);
    }

    return res;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<string> strs1 = {"flower", "flow", "flight"};
  string result1 = solution.longestCommonPrefix(strs1);
  cout << "Test 1: \"" << result1 << "\" (Expected: \"fl\")" << endl;

  // Test Case 2
  vector<string> strs2 = {"dog", "racecar", "car"};
  string result2 = solution.longestCommonPrefix(strs2);
  cout << "Test 2: \"" << result2 << "\" (Expected: \"\")" << endl;

  return 0;
}
