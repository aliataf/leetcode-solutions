/*
 * Problem: 118. Pascal's Triangle
 * Link: https://leetcode.com/problems/pascals-triangle/
 * Difficulty: Easy
 *
 * Description:
 * Given an integer numRows, return the first numRows of Pascal's triangle.
 * In Pascal's triangle, each number is the sum of the two numbers directly
 * above it.
 *
 * Example:
 * Input: numRows = 5
 * Output: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
 *
 * Input: numRows = 1
 * Output: [[1]]
 *
 * Constraints:
 * - 1 <= numRows <= 30
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
  public:
    /*
     * Approach: Build row by row using previous row values
     *
     * Strategy:
     * 1. Handle base cases for numRows 1 and 2.
     * 2. For each subsequent row i (1-indexed from 3):
     *    - Create a new row of size i.
     *    - Set first and last elements to 1.
     *    - Fill the middle elements using the sum of two elements from the
     * previous row.
     *    - Use symmetry: row[j] = row[i-j-1] to fill both sides at once.
     *
     * Time Complexity: O(numRows^2)
     * Space Complexity: O(1) extra space (excluding the result)
     */
    vector<vector<int>> generate(int numRows) {
        if (numRows == 1) return {{1}};
        if (numRows == 2) return {{1}, {1, 1}};
        vector<vector<int>> res = {{1}, {1, 1}};
        for (int i = 3; i <= numRows; i++) {
            vector<int> row(i);
            row[0] = row[i - 1] = 1;
            for (int j = 1; j <= i / 2; j++) {
                row[j] = row[i - j - 1] = res[i - 2][j - 1] + res[i - 2][j];
            }
            res.push_back(row);
        }
        return res;
    }
};

// ============== Test Cases ==============
void printResult(const vector<vector<int>> &result) {
    cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < result[i].size(); ++j) {
            cout << result[i][j];
            if (j < result[i].size() - 1) cout << ",";
        }
        cout << "]";
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // Test Case 1
    int numRows1 = 5;
    vector<vector<int>> result1 = solution.generate(numRows1);
    cout << "Test 1: ";
    printResult(result1);
    // Expected: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]

    // Test Case 2
    int numRows2 = 1;
    vector<vector<int>> result2 = solution.generate(numRows2);
    cout << "Test 2: ";
    printResult(result2);
    // Expected: [[1]]

    return 0;
}
