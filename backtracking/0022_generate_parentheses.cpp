/*
 * Problem: 22. Generate Parentheses
 * Link: https://leetcode.com/problems/generate-parentheses/
 * Difficulty: Medium
 *
 * Description:
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 *
 * Example:
 * Input: n = 3
 * Output: ["((()))","(()())","(())()","()(())","()()()"]
 *
 * Input: n = 1
 * Output: ["()"]
 *
 * Constraints:
 * - 1 <= n <= 8
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Backtracking
   * Use recursion to build the string. Keep track of the number of open and
   * close parentheses used. We can add an open parenthesis if open < n. We can
   * add a close parenthesis if close < open. When the string length reaches
   * 2*n, we have a valid combination.
   *
   * Time Complexity: O(4^n / sqrt(n)) - Catalan number
   * Space Complexity: O(n) for recursion stack and string storage
   */
  vector<string> generateParenthesis(int n) {
    vector<string> v;
    helper("", v, 0, 0, n);
    return v;
  }

  void helper(string s, vector<string> &v, int open, int close, int max) {
    if (s.size() == 2 * max) {
      v.push_back(s);
      return;
    }
    if (open < max)
      helper(s + "(", v, open + 1, close, max);
    if (close < open)
      helper(s + ")", v, open, close + 1, max);
  }
};

// ============== Test Cases ==============
void printResult(const vector<string> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    cout << "\"" << result[i] << "\"" << (i < result.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  int n1 = 3;
  vector<string> result1 = solution.generateParenthesis(n1);
  cout << "Test 1 (n=3): ";
  printResult(result1);
  // Expected: ["((()))","(()())","(())()","()(())","()()()"]

  // Test Case 2
  int n2 = 1;
  vector<string> result2 = solution.generateParenthesis(n2);
  cout << "Test 2 (n=1): ";
  printResult(result2);
  // Expected: ["()"]

  return 0;
}
