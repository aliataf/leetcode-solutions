/*
 * Problem: 42. Trapping Rain Water
 * Link: https://leetcode.com/problems/trapping-rain-water/
 * Difficulty: Hard
 *
 * Description:
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 *
 * Example:
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The elevation map (black section) is represented by array
 * [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section)
 * are being trapped.
 *
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 *
 * Constraints:
 * - n == height.length
 * - 1 <= n <= 2 * 10^4
 * - 0 <= height[i] <= 10^5
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Two Pointers
   *
   * Key Insight: Water trapped at position i = min(maxLeft, maxRight) -
   * height[i]
   *
   * Instead of computing maxLeft and maxRight for every position separately,
   * we use two pointers starting from both ends and track running maximums.
   *
   * Strategy:
   * 1. Start with pointers at both ends (l=0, r=n-1)
   * 2. Track maxL (max height from left) and maxR (max height from right)
   * 3. Always process the side with the smaller max height:
   *    - If maxL ≤ maxR: water at position l is limited by maxL
   *      (we know there's a taller or equal bar on the right)
   *      Add (maxL - height[l]) to result, update maxL, move l forward
   *    - Otherwise: water at position r is limited by maxR
   *      Add (maxR - height[r]) to result, update maxR, move r backward
   *
   * Why this works: When we process a position, we're guaranteed that the
   * limiting factor (smaller of the two maxes) has been determined, even if
   * we don't know the exact maximum on the other side yet.
   *
   * Time Complexity: O(n) - single pass through the array
   * Space Complexity: O(1) - only using a few variables
   */
  int trap(vector<int> &height) {
    int res = 0, l = 0, r = height.size() - 1;
    int maxL = height[l], maxR = height[r];
    while (l <= r) {
      if (maxL <= maxR) {
        res += max(maxL - height[l], 0);
        maxL = max(maxL, height[l]);
        l++;
      } else {
        res += max(maxR - height[r], 0);
        maxR = max(maxR, height[r]);
        r--;
      }
    }

    return res;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  int result1 = solution.trap(height1);
  cout << "Test 1: " << result1 << " (Expected: 6)" << endl;

  // Test Case 2
  vector<int> height2 = {4, 2, 0, 3, 2, 5};
  int result2 = solution.trap(height2);
  cout << "Test 2: " << result2 << " (Expected: 9)" << endl;

  // Test Case 3
  vector<int> height3 = {3, 0, 2, 0, 4};
  int result3 = solution.trap(height3);
  cout << "Test 3: " << result3 << " (Expected: 7)" << endl;

  return 0;
}
