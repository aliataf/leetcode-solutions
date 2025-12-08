/*
 * Problem: 64. Minimum Path Sum
 * Link: https://leetcode.com/problems/minimum-path-sum/
 * Difficulty: Medium
 *
 * Description:
 * Given a m x n grid filled with non-negative numbers, find a path from top
 * left to bottom right, which minimizes the sum of all numbers along its path.
 * Note: You can only move either down or right at any point in time.
 *
 * Example:
 * Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
 * Output: 7
 * Explanation: The path 1 → 3 → 1 → 1 → 1 minimizes the sum.
 *
 * Input: grid = [[1,2,3],[4,5,6]]
 * Output: 12
 *
 * Constraints:
 * - m == grid.length
 * - n == grid[i].length
 * - 1 <= m, n <= 200
 * - 0 <= grid[i][j] <= 200
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Bottom-Up DP
   *
   * Key Insight: The minimum sum to reach any cell (i,j) is the cell's value
   * plus the smaller of the minimum sums to reach (i-1,j) or (i,j-1).
   *
   * Strategy:
   * Build the solution from top-left corner. First fill the first row and
   * column (only one path possible for each). Then for each remaining cell,
   * take the minimum of coming from above or from the left.
   *
   * Time Complexity: O(m * n)
   * Space Complexity: O(m * n) - uses copy of grid as dp table
   */
  int minPathSum(vector<vector<int>> &grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp = grid;

    for (int i = 1; i < m; i++) {
      dp[i][0] += dp[i - 1][0];
    }

    for (int j = 1; j < n; j++) {
      dp[0][j] += dp[0][j - 1];
    }

    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        dp[i][j] += min(dp[i - 1][j], dp[i][j - 1]);
      }
    }

    return dp[m - 1][n - 1];
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<vector<int>> grid1 = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
  cout << "Test 1: " << solution.minPathSum(grid1) << " (Expected: 7)" << endl;

  // Test Case 2
  vector<vector<int>> grid2 = {{1, 2, 3}, {4, 5, 6}};
  cout << "Test 2: " << solution.minPathSum(grid2) << " (Expected: 12)" << endl;

  return 0;
}
