/*
 * Problem: 84. Largest Rectangle in Histogram
 * Link: https://leetcode.com/problems/largest-rectangle-in-histogram/
 * Difficulty: Hard
 *
 * Description:
 * Given an array of integers heights representing the histogram's bar height
 * where the width of each bar is 1, return the area of the largest rectangle in
 * the histogram.
 *
 * Example:
 * Input: heights = [2,1,5,6,2,3]
 * Output: 10
 * Explanation: The largest rectangle has an area = 10 units.
 *
 * Input: heights = [2,4]
 * Output: 4
 *
 * Constraints:
 * - 1 <= heights.length <= 10^5
 * - 0 <= heights[i] <= 10^4
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Monotonic Stack
   *
   * Strategy:
   * 1. Use a stack to store pairs of (index, height). The stack will maintain
   * bars in increasing order of height.
   * 2. Iterate through the histogram:
   *    - If the current bar is higher than the stack top, push it.
   *    - If the current bar is lower, it means the rectangle defined by the
   * stack top cannot extend further to the right. Pop the stack top and
   * calculate the area: height = popped_height, width = current_index -
   * popped_index. Update max area. The start index of the current bar should be
   * the index of the last popped element (because the current bar could extend
   * leftwards into the popped area).
   * 3. After iterating, process remaining bars in the stack. They extend to the
   * end of the histogram (width = n - popped_index).
   *
   * Time Complexity: O(n)
   * Space Complexity: O(n)
   */
  int largestRectangleArea(vector<int> &heights) {
    stack<pair<int, int>> s;
    int n = heights.size(), res = 0;
    for (int i = 0; i < n; i++) {
      int start = i;
      while (!s.empty() && heights[i] < s.top().second) {
        pair<int, int> p = s.top();
        s.pop();
        res = max(res, (i - p.first) * p.second);
        start = p.first;
      }
      s.push({start, heights[i]});
    }
    while (!s.empty()) {
      pair<int, int> p = s.top();
      s.pop();
      res = max(res, (n - p.first) * p.second);
    }

    return res;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> heights1 = {2, 1, 5, 6, 2, 3};
  int result1 = solution.largestRectangleArea(heights1);
  cout << "Test 1: " << result1 << " (Expected: 10)" << endl;

  // Test Case 2
  vector<int> heights2 = {2, 4};
  int result2 = solution.largestRectangleArea(heights2);
  cout << "Test 2: " << result2 << " (Expected: 4)" << endl;

  return 0;
}
