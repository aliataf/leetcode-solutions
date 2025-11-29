/*
 * Problem: 54. Spiral Matrix
 * Link: https://leetcode.com/problems/spiral-matrix/
 * Difficulty: Medium
 *
 * Description:
 * Given an m x n matrix, return all elements of the matrix in spiral order.
 *
 * Example:
 * Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: [1,2,3,6,9,8,7,4,5]
 *
 * Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 * Constraints:
 * - m == matrix.length
 * - n == matrix[i].length
 * - 1 <= m, n <= 10
 * - -100 <= matrix[i][j] <= 100
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Layer-by-layer traversal with boundary tracking
   *
   * Key Insight: Traverse the matrix in a spiral by processing one layer at a
   * time, moving from outer to inner layers. Each layer consists of four sides.
   *
   * Strategy:
   * 1. Maintain four boundaries: top, bottom, left, right
   * 2. For each layer, traverse in order:
   *    - Left to right along the top row
   *    - Top to bottom along the right column
   *    - Right to left along the bottom row (if still valid)
   *    - Bottom to top along the left column (if still valid)
   * 3. After each side, shrink the corresponding boundary
   * 4. Continue until boundaries cross
   *
   * The extra checks (top <= bottom, left <= right) prevent duplicate elements
   * when the matrix has odd dimensions.
   *
   * Time Complexity: O(m * n) - visit each element once
   * Space Complexity: O(1) - excluding the result vector
   */
  vector<int> spiralOrder(vector<vector<int>> &matrix) {
    vector<int> result;

    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;

    while (top <= bottom && left <= right) {
      for (int j = left; j <= right; j++) {
        result.push_back(matrix[top][j]);
      }
      top++;

      for (int i = top; i <= bottom; i++) {
        result.push_back(matrix[i][right]);
      }
      right--;

      if (top <= bottom) {
        for (int j = right; j >= left; j--) {
          result.push_back(matrix[bottom][j]);
        }
        bottom--;
      }

      if (left <= right) {
        for (int i = bottom; i >= top; i--) {
          result.push_back(matrix[i][left]);
        }
        left++;
      }
    }

    return result;
  }
};

// ============== Test Cases ==============
void printResult(const vector<int> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i < result.size() - 1)
      cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  vector<vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<int> result1 = solution.spiralOrder(matrix1);
  cout << "Test 1: ";
  printResult(result1);
  // Expected: [1,2,3,6,9,8,7,4,5]

  // Test Case 2
  vector<vector<int>> matrix2 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
  vector<int> result2 = solution.spiralOrder(matrix2);
  cout << "Test 2: ";
  printResult(result2);
  // Expected: [1,2,3,4,8,12,11,10,9,5,6,7]

  // Test Case 3
  vector<vector<int>> matrix3 = {{1}};
  vector<int> result3 = solution.spiralOrder(matrix3);
  cout << "Test 3: ";
  printResult(result3);
  // Expected: [1]

  return 0;
}
