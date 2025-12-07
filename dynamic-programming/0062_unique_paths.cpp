/*
 * Problem: 62. Unique Paths
 * Link: https://leetcode.com/problems/unique-paths/
 * Difficulty: Medium
 *
 * Description:
 * There is a robot on an m x n grid. The robot is initially located at the
 * top-left corner and tries to move to the bottom-right corner. The robot can
 * only move either down or right. Given the two integers m and n, return the
 * number of possible unique paths.
 *
 * Example:
 * Input: m = 3, n = 7
 * Output: 28
 *
 * Input: m = 3, n = 2
 * Output: 3
 *
 * Constraints:
 * - 1 <= m, n <= 100
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Top-Down DP with Memoization
   *
   * Key Insight: From any cell (i,j), the number of paths to the destination
   * is the sum of paths from (i+1,j) and (i,j+1). This creates overlapping
   * subproblems, making memoization effective.
   *
   * Strategy:
   * Recursively explore all paths going right or down. Cache results to avoid
   * recomputing the same cell. Base case: reaching destination returns 1,
   * going out of bounds returns 0.
   *
   * Time Complexity: O(m * n)
   * Space Complexity: O(m * n)
   */
  int uniquePaths(int m, int n) {
    vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));
    return helper(m, n, 1, 1, memo);
  }

  int helper(int m, int n, int i, int j, vector<vector<int>> &memo) {
    if (i > m || j > n) return 0;
    if (i == m && j == n) return 1;
    if (memo[i][j] != -1) return memo[i][j];
    return memo[i][j] =
               helper(m, n, i + 1, j, memo) + helper(m, n, i, j + 1, memo);
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  cout << "Test 1: " << solution.uniquePaths(3, 7) << " (Expected: 28)" << endl;
  cout << "Test 2: " << solution.uniquePaths(3, 2) << " (Expected: 3)" << endl;
  cout << "Test 3: " << solution.uniquePaths(1, 1) << " (Expected: 1)" << endl;

  return 0;
}
