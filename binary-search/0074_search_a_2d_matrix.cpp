/*
 * Problem: 74. Search a 2D Matrix
 * Link: https://leetcode.com/problems/search-a-2d-matrix/
 * Difficulty: Medium
 *
 * Description:
 * You are given an m x n integer matrix matrix with the following two
 * properties:
 * 1. Each row is sorted in non-decreasing order.
 * 2. The first integer of each row is greater than the last integer of the
 * previous row. Given an integer target, return true if target is in matrix or
 * false otherwise. You must write a solution in O(log(m * n)) time complexity.
 *
 * Example:
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
 * Output: true
 *
 * Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
 * Output: false
 *
 * Constraints:
 * - m == matrix.length
 * - n == matrix[i].length
 * - 1 <= m, n <= 100
 * - -10^4 <= matrix[i][j], target <= 10^4
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Binary Search on Flattened Matrix
   *
   * Key Insight: Since the matrix is sorted row by row and the first element of
   * a row is greater than the last element of the previous row, the entire
   * matrix can be treated as a single sorted array of size m * n.
   *
   * Strategy:
   * 1. Treat the 2D matrix as a 1D array of size m * n.
   * 2. Perform standard binary search with range [0, m * n - 1].
   * 3. Map 1D index 'middle' back to 2D coordinates:
   *    - row = middle / n
   *    - col = middle % n
   * 4. Compare matrix[row][col] with target and adjust search range.
   *
   * Time Complexity: O(log(m * n))
   * Space Complexity: O(1)
   */
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int lo = 0, hi = m * n - 1;
    while (lo <= hi) {
      int middle = (lo + hi) / 2;
      int i = middle / n;
      int j = middle % n;
      if (matrix[i][j] == target) {
        return true;
      } else if (matrix[i][j] > target) {
        hi = hi - 1;
      } else {
        lo = lo + 1;
      }
    }

    return false;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<vector<int>> matrix1 = {
      {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  int target1 = 3;
  bool result1 = solution.searchMatrix(matrix1, target1);
  cout << "Test 1: " << (result1 ? "true" : "false") << " (Expected: true)"
       << endl;

  // Test Case 2
  vector<vector<int>> matrix2 = {
      {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  int target2 = 13;
  bool result2 = solution.searchMatrix(matrix2, target2);
  cout << "Test 2: " << (result2 ? "true" : "false") << " (Expected: false)"
       << endl;

  // Test Case 3
  vector<vector<int>> matrix3 = {{1}};
  int target3 = 1;
  bool result3 = solution.searchMatrix(matrix3, target3);
  cout << "Test 3: " << (result3 ? "true" : "false") << " (Expected: true)"
       << endl;

  return 0;
}
