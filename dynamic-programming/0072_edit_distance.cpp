/*
 * Problem: 72. Edit Distance
 * Link: https://leetcode.com/problems/edit-distance/
 * Difficulty: Medium
 *
 * Description:
 * Given two strings word1 and word2, return the minimum number of operations
 * required to convert word1 to word2. You have the following three operations
 * permitted on a word:
 * - Insert a character
 * - Delete a character
 * - Replace a character
 *
 * Example:
 * Input: word1 = "horse", word2 = "ros"
 * Output: 3
 * Explanation:
 * horse -> rorse (replace 'h' with 'r')
 * rorse -> rose (remove 'r')
 * rose -> ros (remove 'e')
 *
 * Input: word1 = "intention", word2 = "execution"
 * Output: 5
 * Explanation:
 * intention -> inention (remove 't')
 * inention -> enention (replace 'i' with 'e')
 * enention -> exention (replace 'n' with 'x')
 * exention -> exection (replace 'n' with 'c')
 * exection -> execution (insert 'u')
 *
 * Constraints:
 * - 0 <= word1.length, word2.length <= 500
 * - word1 and word2 consist of lowercase English letters.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct pair_hash {
  size_t operator()(const pair<int, int> &p) const {
    return (long long)p.first << 32 ^ p.second;
  }
};

class Solution {
public:
  /*
   * Approach: Top-Down Dynamic Programming (Memoization)
   *
   * Strategy:
   * 1. Define a helper function that takes the current lengths of the two
   * strings (n, m).
   * 2. Base cases:
   *    - If word1 is empty (n=0), we need m insertions.
   *    - If word2 is empty (m=0), we need n deletions.
   * 3. Recursive step:
   *    - If characters match (s[n-1] == t[m-1]), no operation needed, recurse
   * on (n-1, m-1).
   *    - If mismatch, take the minimum of 3 operations + 1:
   *      - Insert: helper(n, m-1)
   *      - Delete: helper(n-1, m)
   *      - Replace: helper(n-1, m-1)
   * 4. Use a hash map to memoize results for state (n, m) to avoid
   * re-computation.
   *
   * Time Complexity: O(n * m)
   * Space Complexity: O(n * m) for the recursion stack and hash map
   */
  unordered_map<pair<int, int>, int, pair_hash> mp;
  int minDistance(string word1, string word2) {
    return helper(word1, word2, word1.length(), word2.length());
  }

  int helper(string &s, string &t, int n, int m) {
    pair<int, int> key = {n, m};
    if (mp.find(key) != mp.end()) return mp[key];
    if (n == 0) return m;
    if (m == 0) return n;
    if (s[n - 1] == t[m - 1]) return mp[key] = helper(s, t, n - 1, m - 1);

    return mp[key] =
               1 + min(helper(s, t, n - 1, m),
                       min(helper(s, t, n, m - 1), helper(s, t, n - 1, m - 1)));
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  string word1 = "horse";
  string word2 = "ros";
  // Since we use a class instance, we should ideally clear map or use new
  // instance. For simplicity in this test runner, we'll just use new instance.
  // The keys (len1, len2) might collide if we ran multiple calls on same
  // instance with different strings of same length.

  Solution s1;
  cout << "Test 1: " << s1.minDistance(word1, word2) << " (Expected: 3)"
       << endl;

  // Test Case 2
  string word3 = "intention";
  string word4 = "execution";
  Solution s2;
  cout << "Test 2: " << s2.minDistance(word3, word4) << " (Expected: 5)"
       << endl;

  // Test Case 3
  string word5 = "";
  string word6 = "a";
  Solution s3;
  cout << "Test 3: " << s3.minDistance(word5, word6) << " (Expected: 1)"
       << endl;

  return 0;
}
