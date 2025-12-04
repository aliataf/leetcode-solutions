/*
 * Problem: 70. Climbing Stairs
 * Link: https://leetcode.com/problems/climbing-stairs/
 * Difficulty: Easy
 *
 * Description:
 * You are climbing a staircase. It takes n steps to reach the top.
 * Each time you can either climb 1 or 2 steps. In how many distinct ways can
 * you climb to the top?
 *
 * Example:
 * Input: n = 2
 * Output: 2
 * Explanation: There are two ways to climb to the top.
 * 1. 1 step + 1 step
 * 2. 2 steps
 *
 * Input: n = 3
 * Output: 3
 * Explanation: There are three ways to climb to the top.
 * 1. 1 step + 1 step + 1 step
 * 2. 1 step + 2 steps
 * 3. 2 steps + 1 step
 *
 * Constraints:
 * - 1 <= n <= 45
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Dynamic Programming (Fibonacci Sequence)
   *
   * Key Insight: To reach step i, you could have come from:
   * 1. Step i-1 (by taking 1 step)
   * 2. Step i-2 (by taking 2 steps)
   *
   * Therefore, the total number of ways to reach step i is the sum of ways to
   * reach step i-1 and step i-2 (fibonacci sequence).
   * This forms the recurrence relation: ways(i) = ways(i-1) + ways(i-2)
   *
   * Strategy:
   * 1. Base cases:
   *    - 1 way to reach step 1 (1)
   *    - 2 ways to reach step 2 (1+1, 2)
   *    - 3 ways to reach step 3 (1+1+1, 1+2, 2+1)
   *    - Generally for n < 4, result is n.
   * 2. For n >= 4, use the recurrence relation to build up the solution.
   * 3. Use a vector to store the results (memoization/tabulation).
   *
   * Time Complexity: O(n) - one pass to calculate up to n
   * Space Complexity: O(n) - to store the ways for each step
   */
  int climbStairs(int n) {
    if (n < 4) return n;
    vector<int> s(n + 1);
    s[1] = 1;
    s[2] = 2;
    for (int i = 3; i <= n; i++) {
      s[i] = s[i - 1] + s[i - 2];
    }

    return s[n];
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  int n1 = 2;
  int result1 = solution.climbStairs(n1);
  cout << "Test 1: " << result1 << " (Expected: 2)" << endl;

  // Test Case 2
  int n2 = 3;
  int result2 = solution.climbStairs(n2);
  cout << "Test 2: " << result2 << " (Expected: 3)" << endl;

  // Test Case 3
  int n3 = 4;
  int result3 = solution.climbStairs(n3);
  cout << "Test 3: " << result3 << " (Expected: 5)" << endl;

  // Test Case 4
  int n4 = 5;
  int result4 = solution.climbStairs(n4);
  cout << "Test 4: " << result4 << " (Expected: 8)" << endl;

  return 0;
}
