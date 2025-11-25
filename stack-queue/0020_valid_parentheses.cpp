/*
 * Problem: 20. Valid Parentheses
 * Link: https://leetcode.com/problems/valid-parentheses/
 * Difficulty: Easy
 *
 * Description:
 * Given a string s containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 *
 * An input string is valid if:
 * 1. Open brackets must be closed by the same type of brackets.
 * 2. Open brackets must be closed in the correct order.
 * 3. Every close bracket has a corresponding open bracket of the same type.
 *
 * Example:
 * Input: s = "()"
 * Output: true
 *
 * Input: s = "()[]{}"
 * Output: true
 *
 * Input: s = "(]"
 * Output: false
 *
 * Constraints:
 * - 1 <= s.length <= 10^4
 * - s consists of parentheses only '()[]{}'.
 */

#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
  /*
   * Approach: Stack
   * Use a stack to keep track of opening brackets. When a closing bracket is
   * encountered, check if the stack is empty or if the top of the stack matches
   * the corresponding opening bracket. If valid, pop from stack. Finally, check
   * if stack is empty.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(n)
   */
  bool isValid(string s) {
    stack<char> st;
    unordered_map<char, char> um = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
    for (int i = 0, n = s.size(); i < n; i++) {
      if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
        st.push(s[i]);
      } else {
        if (st.empty() || um[st.top()] != s[i])
          return false;
        st.pop();
      }
    }

    return st.empty();
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  string s1 = "()";
  bool result1 = solution.isValid(s1);
  cout << "Test 1: " << (result1 ? "true" : "false") << " (Expected: true)"
       << endl;

  // Test Case 2
  string s2 = "()[]{}";
  bool result2 = solution.isValid(s2);
  cout << "Test 2: " << (result2 ? "true" : "false") << " (Expected: true)"
       << endl;

  // Test Case 3
  string s3 = "(]";
  bool result3 = solution.isValid(s3);
  cout << "Test 3: " << (result3 ? "true" : "false") << " (Expected: false)"
       << endl;

  return 0;
}
