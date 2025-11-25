/*
 * Problem: 36. Valid Sudoku
 * Link: https://leetcode.com/problems/valid-sudoku/
 * Difficulty: Medium
 *
 * Description:
 * Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be
 * validated according to the following rules:
 * 1. Each row must contain the digits 1-9 without repetition.
 * 2. Each column must contain the digits 1-9 without repetition.
 * 3. Each of the nine 3 x 3 sub-boxes must contain the digits 1-9 without
 * repetition.
 *
 * Note:
 * - A Sudoku board (partially filled) could be valid but is not necessarily
 * solvable.
 * - Only the filled cells need to be validated according to the mentioned
 * rules.
 *
 * Example:
 * Input: board =
 * [["5","3",".",".","7",".",".",".","."]
 * ,["6",".",".","1","9","5",".",".","."]
 * ,[".","9","8",".",".",".",".","6","."]
 * ,["8",".",".",".","6",".",".",".","3"]
 * ,["4",".",".","8",".","3",".",".","1"]
 * ,["7",".",".",".","2",".",".",".","6"]
 * ,[".","6",".",".",".",".","2","8","."]
 * ,[".",".",".","4","1","9",".",".","5"]
 * ,[".",".",".",".","8",".",".","7","9"]]
 * Output: true
 *
 * Constraints:
 * - board.length == 9
 * - board[i].length == 9
 * - board[i][j] is a digit 1-9 or '.'.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Validate rows, columns, and 3x3 sub-boxes
   * 1. Create a transposed board to easily check columns
   * 2. Check each row and column for duplicates
   * 3. Check each 3x3 sub-box for duplicates
   *
   * Time Complexity: O(1) - board is always 9x9
   * Space Complexity: O(1) - fixed size arrays
   */
  bool isValidSudoku(vector<vector<char>> &board) {
    vector<vector<char>> boardT(9, vector<char>(9, 'a'));
    for (int i = 0; i < board.size(); i++) {
      for (int j = 0; j < board[i].size(); j++) {
        boardT[j][i] = board[i][j];
        if (i % 3 == 0 && j % 3 == 0) {
          if (!isValidSubBox(board, i, j)) {
            return false;
          }
        }
      }
    }
    for (int i = 0; i < board.size(); i++) {
      if (!isValidSequence(board[i])) {
        return false;
      }
      if (!isValidSequence(boardT[i])) {
        return false;
      }
    }

    return true;
  }

  bool isValidSequence(vector<char> &sequence) {
    bool numbers[9] = {0};
    for (int i = 0; i < sequence.size(); i++) {
      if (sequence[i] != '.') {
        if (numbers[sequence[i] - '1']) {
          return false;
        }
        numbers[sequence[i] - '1'] = 1;
      }
    }

    return true;
  }

  bool isValidSubBox(vector<vector<char>> &board, int row, int column) {
    bool numbers[9] = {0};
    for (int i = row; i < row + 3; i++) {
      for (int j = column; j < column + 3; j++) {
        if (board[i][j] != '.') {
          if (numbers[(board[i][j] - '1')]) {
            return false;
          }
          numbers[board[i][j] - '1'] = 1;
        }
      }
    }

    return true;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1: Valid Sudoku
  vector<vector<char>> board1 = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  bool result1 = solution.isValidSudoku(board1);
  cout << "Test 1: " << (result1 ? "true" : "false") << " (Expected: true)"
       << endl;

  // Test Case 2: Invalid Sudoku (duplicate in row)
  vector<vector<char>> board2 = {{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                                 {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                 {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                 {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                 {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                 {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                 {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                 {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                 {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  bool result2 = solution.isValidSudoku(board2);
  cout << "Test 2: " << (result2 ? "true" : "false") << " (Expected: false)"
       << endl;

  return 0;
}
