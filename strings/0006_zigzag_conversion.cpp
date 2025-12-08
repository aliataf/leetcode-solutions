/*
 * Problem: 6. Zigzag Conversion
 * Link: https://leetcode.com/problems/zigzag-conversion/
 * Difficulty: Medium
 *
 * Description:
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 * of rows like this: (you may want to display this pattern in a fixed font for
 * better legibility) P   A   H   N A P L S I I G Y   I   R And then read line
 * by line: "PAHNAPLSIIGYIR" Write the code that will take a string and make
 * this conversion given a number of rows.
 *
 * Example:
 * Input: s = "PAYPALISHIRING", numRows = 3
 * Output: "PAHNAPLSIIGYIR"
 *
 * Input: s = "PAYPALISHIRING", numRows = 4
 * Output: "PINALSIGYAHRPI"
 *
 * Constraints:
 * - 1 <= s.length <= 1000
 * - s consists of English letters (lower-case and upper-case), ',' and '.'.
 * - 1 <= numRows <= 1000
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Simulate the Zigzag Pattern
   *
   * Key Insight: Instead of building a 2D grid, we can use separate strings
   * for each row and append characters as we traverse down and up the rows.
   *
   * Strategy:
   * Traverse the string while maintaining the current row and direction.
   * When we hit the top (row 0) or bottom (row numRows-1), we reverse
   * direction. Finally, concatenate all row strings to get the result.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(n)
   */
  string convert(string s, int numRows) {
    if (numRows == 1 || s.size() <= numRows) return s;

    vector<string> rows(numRows);
    int currentRow = 0;
    bool isGoingDown = false;

    for (char c : s) {
      rows[currentRow] += c;
      if (currentRow == 0 || currentRow == numRows - 1) {
        isGoingDown = !isGoingDown;
      }
      currentRow += isGoingDown ? 1 : -1;
    }

    string result;
    for (string &row : rows) result += row;
    return result;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  cout << "Test 1: " << solution.convert("PAYPALISHIRING", 3)
       << " (Expected: PAHNAPLSIIGYIR)" << endl;
  cout << "Test 2: " << solution.convert("PAYPALISHIRING", 4)
       << " (Expected: PINALSIGYAHRPI)" << endl;
  cout << "Test 3: " << solution.convert("A", 1) << " (Expected: A)" << endl;

  return 0;
}
