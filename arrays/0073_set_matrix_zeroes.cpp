/*
 * Problem: 73. Set Matrix Zeroes
 * Link: https://leetcode.com/problems/set-matrix-zeroes/
 * Difficulty: Medium
 *
 * Description:
 * Given an m x n integer matrix, if an element is 0, set its entire row and
 * column to 0's. You must do it in place.
 *
 * Example 1:
 * Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
 * Output: [[1,0,1],[0,0,0],[1,0,1]]
 *
 * Example 2:
 * Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
 * Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
 *
 * Constraints:
 * - m == matrix.length
 * - n == matrix[0].length
 * - 1 <= m, n <= 200
 * - -2^31 <= matrix[i][j] <= 2^31 - 1
 *
 * Follow up: Devise a constant space solution.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: In-Place Marking Using First Row and Column
   *
   * Key Insight: We need to know which rows and columns to zero, but we can't
   * afford O(m+n) extra space for the follow-up. The first row and column can
   * double as the marker storage — matrix[0][j] = 0 means column j must be
   * zeroed, and matrix[i][0] = 0 means row i must be zeroed. The only
   * complication is that the first row/column themselves might originally
   * contain zeros, so we record that separately in two booleans before reusing
   * them as markers.
   *
   * Strategy:
   * 1. Scan the first row and first column; record whether each originally
   *    contains a zero in `firstRowZero` / `firstColZero`.
   * 2. For every inner cell (i >= 1, j >= 1) that is zero, mark matrix[i][0]
   *    and matrix[0][j] as zero.
   * 3. Second pass over inner cells: zero out matrix[i][j] if its row marker
   *    or column marker is zero.
   * 4. Finally, zero the first row and/or first column based on the booleans.
   *    This step must come last so the markers stay readable through step 3.
   *
   * Time Complexity: O(m * n) - constant number of passes over the matrix.
   * Space Complexity: O(1) - only two boolean flags beyond the input.
   */
  void setZeroes(vector<vector<int>> &matrix) {
    int m = matrix.size(), n = matrix[0].size();
    bool firstRowZero = false, firstColZero = false;

    for (int j = 0; j < n; j++)
      if (matrix[0][j] == 0) firstRowZero = true;
    for (int i = 0; i < m; i++)
      if (matrix[i][0] == 0) firstColZero = true;

    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (matrix[i][j] == 0) {
          matrix[i][0] = 0;
          matrix[0][j] = 0;
        }
      }
    }

    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (matrix[i][0] == 0 || matrix[0][j] == 0) {
          matrix[i][j] = 0;
        }
      }
    }

    if (firstRowZero)
      for (int j = 0; j < n; j++) matrix[0][j] = 0;
    if (firstColZero)
      for (int i = 0; i < m; i++) matrix[i][0] = 0;
  }
};

// ============== Test Cases ==============
void printMatrix(const vector<vector<int>> &matrix) {
  cout << "[";
  for (size_t i = 0; i < matrix.size(); ++i) {
    cout << "[";
    for (size_t j = 0; j < matrix[i].size(); ++j) {
      cout << matrix[i][j];
      if (j + 1 < matrix[i].size()) cout << ",";
    }
    cout << "]";
    if (i + 1 < matrix.size()) cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  vector<vector<int>> matrix1 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  solution.setZeroes(matrix1);
  cout << "Test 1: ";
  printMatrix(matrix1);
  // Expected: [[1,0,1],[0,0,0],[1,0,1]]

  // Test Case 2
  vector<vector<int>> matrix2 = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
  solution.setZeroes(matrix2);
  cout << "Test 2: ";
  printMatrix(matrix2);
  // Expected: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]

  // Test Case 3: No zeros
  vector<vector<int>> matrix3 = {{1, 2}, {3, 4}};
  solution.setZeroes(matrix3);
  cout << "Test 3: ";
  printMatrix(matrix3);
  // Expected: [[1,2],[3,4]]

  // Test Case 4: Single cell zero
  vector<vector<int>> matrix4 = {{0}};
  solution.setZeroes(matrix4);
  cout << "Test 4: ";
  printMatrix(matrix4);
  // Expected: [[0]]

  return 0;
}
