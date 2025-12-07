/*
 * Problem: 63. Unique Paths II
 * Link: https://leetcode.com/problems/unique-paths-ii/
 * Difficulty: Medium
 *
 * Description:
 * You are given an m x n integer array grid. There is a robot initially located
 * at the top-left corner. The robot tries to move to the bottom-right corner.
 * The robot can only move either down or right at any point in time. An
 * obstacle and space are marked as 1 or 0 respectively in grid. Return the
 * number of possible unique paths that the robot can take to reach the
 * bottom-right.
 *
 * Example:
 * Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
 * Output: 2
 * Explanation: There is one obstacle in the middle of the 3x3 grid above.
 *
 * Input: obstacleGrid = [[0,1],[0,0]]
 * Output: 1
 *
 * Constraints:
 * - m == obstacleGrid.length
 * - n == obstacleGrid[i].length
 * - 1 <= m, n <= 100
 * - obstacleGrid[i][j] is 0 or 1.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Top-Down DP with Memoization
   *
   * Key Insight: Same as Unique Paths I, but we add a check for obstacles.
   * If a cell contains an obstacle (value 1), no paths can go through it,
   * so we return 0 immediately for that cell.
   *
   * Strategy:
   * Recursively count paths going right or down, caching results. If we hit
   * an obstacle or go out of bounds, return 0. Reaching the destination
   * returns 1.
   *
   * Time Complexity: O(m * n)
   * Space Complexity: O(m * n)
   */
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    vector<vector<int>> memo(m, vector<int>(n, -1));
    return helper(obstacleGrid, m, n, 0, 0, memo);
  }

  int helper(vector<vector<int>> &obstacleGrid, int m, int n, int i, int j,
             vector<vector<int>> &memo) {
    if (i >= m || j >= n) return 0;
    if (obstacleGrid[i][j] == 1) return 0;
    if (i == m - 1 && j == n - 1) return 1;
    if (memo[i][j] != -1) return memo[i][j];
    return memo[i][j] = helper(obstacleGrid, m, n, i + 1, j, memo) +
                        helper(obstacleGrid, m, n, i, j + 1, memo);
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<vector<int>> grid1 = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  cout << "Test 1: " << solution.uniquePathsWithObstacles(grid1)
       << " (Expected: 2)" << endl;

  // Test Case 2
  vector<vector<int>> grid2 = {{0, 1}, {0, 0}};
  cout << "Test 2: " << solution.uniquePathsWithObstacles(grid2)
       << " (Expected: 1)" << endl;

  // Test Case 3: Obstacle at start
  vector<vector<int>> grid3 = {{1, 0}};
  cout << "Test 3: " << solution.uniquePathsWithObstacles(grid3)
       << " (Expected: 0)" << endl;

  return 0;
}
