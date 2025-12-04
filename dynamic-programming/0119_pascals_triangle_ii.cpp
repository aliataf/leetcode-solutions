/*
 * Problem: 119. Pascal's Triangle II
 * Link: https://leetcode.com/problems/pascals-triangle-ii/
 * Difficulty: Easy
 *
 * Description:
 * Given an integer rowIndex, return the rowIndex-th (0-indexed) row of the
 * Pascal's triangle.
 *
 * Example:
 * Input: rowIndex = 3
 * Output: [1,3,3,1]
 *
 * Input: rowIndex = 0
 * Output: [1]
 *
 * Input: rowIndex = 1
 * Output: [1,1]
 *
 * Constraints:
 * - 0 <= rowIndex <= 33
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Build rows iteratively
   *
   * Strategy:
   * 1. Handle base cases for rowIndex 0 and 1.
   * 2. Build the triangle row by row up to rowIndex.
   * 3. Use symmetry to fill each row efficiently.
   * 4. Return the requested row.
   *
   * Time Complexity: O(rowIndex^2)
   * Space Complexity: O(rowIndex^2) for storing all rows
   */
  vector<int> getRow(int rowIndex) {
    if (rowIndex == 0) return {1};
    if (rowIndex == 1) return {1, 1};
    vector<vector<int>> res = {{1}, {1, 1}};
    for (int i = 3; i <= rowIndex + 1; i++) {
      vector<int> row(i);
      row[0] = row[i - 1] = 1;
      for (int j = 1; j <= i / 2; j++) {
        row[j] = row[i - j - 1] = res[i - 2][j - 1] + res[i - 2][j];
      }
      res.push_back(row);
    }
    return res[rowIndex];
  }
};

// ============== Test Cases ==============
void printVector(const vector<int> &vec) {
  cout << "[";
  for (size_t i = 0; i < vec.size(); i++) {
    cout << vec[i];
    if (i < vec.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  int rowIndex1 = 3;
  vector<int> result1 = solution.getRow(rowIndex1);
  cout << "Test 1: ";
  printVector(result1);
  // Expected: [1,3,3,1]

  // Test Case 2
  int rowIndex2 = 0;
  vector<int> result2 = solution.getRow(rowIndex2);
  cout << "Test 2: ";
  printVector(result2);
  // Expected: [1]

  // Test Case 3
  int rowIndex3 = 1;
  vector<int> result3 = solution.getRow(rowIndex3);
  cout << "Test 3: ";
  printVector(result3);
  // Expected: [1,1]

  // Test Case 4
  int rowIndex4 = 4;
  vector<int> result4 = solution.getRow(rowIndex4);
  cout << "Test 4: ";
  printVector(result4);
  // Expected: [1,4,6,4,1]

  return 0;
}
