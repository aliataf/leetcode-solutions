/*
 * Problem: 55. Jump Game
 * Link: https://leetcode.com/problems/jump-game/
 * Difficulty: Medium
 *
 * Description:
 * You are given an integer array nums. You are initially positioned at the
 * array's first index, and each element in the array represents your maximum
 * jump length at that position. Return true if you can reach the last index, or
 * false otherwise.
 *
 * Example:
 * Input: nums = [2,3,1,1,4]
 * Output: true
 * Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
 *
 * Input: nums = [3,2,1,0,4]
 * Output: false
 * Explanation: You will always arrive at index 3 no matter what. Its maximum
 * jump length is 0, which makes it impossible to reach the last index.
 *
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - 0 <= nums[i] <= 10^5
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Greedy - Track Maximum Reachable Position
   *
   * Key Insight: We only need to track the farthest position we can reach.
   * If at any point we can't move forward (stuck at 0 with maxPos <= current
   * position), we can't reach the end.
   *
   * Strategy:
   * 1. Iterate through the array, tracking maxPos (farthest reachable index)
   * 2. At each position i, update maxPos = max(maxPos, i + nums[i])
   * 3. If maxPos reaches or exceeds the last index, return true
   * 4. If we encounter a 0 and can't jump past it (maxPos <= i), return false
   * 5. If we complete the loop, we can reach the end
   *
   * Time Complexity: O(n) - single pass through the array
   * Space Complexity: O(1) - only using a few variables
   */
  bool canJump(vector<int> &nums) {
    int maxPos = 0, n = nums.size();

    for (int i = 0; i < n; i++) {
      maxPos = max(maxPos, i + nums[i]);
      if (maxPos >= n - 1) {
        return true;
      }
      if (nums[i] == 0 && maxPos <= i) {
        return false;
      }
    }

    return true;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {2, 3, 1, 1, 4};
  bool result1 = solution.canJump(nums1);
  cout << "Test 1: " << (result1 ? "true" : "false") << " (Expected: true)"
       << endl;

  // Test Case 2
  vector<int> nums2 = {3, 2, 1, 0, 4};
  bool result2 = solution.canJump(nums2);
  cout << "Test 2: " << (result2 ? "true" : "false") << " (Expected: false)"
       << endl;

  // Test Case 3
  vector<int> nums3 = {0};
  bool result3 = solution.canJump(nums3);
  cout << "Test 3: " << (result3 ? "true" : "false") << " (Expected: true)"
       << endl;

  // Test Case 4
  vector<int> nums4 = {2, 0, 0};
  bool result4 = solution.canJump(nums4);
  cout << "Test 4: " << (result4 ? "true" : "false") << " (Expected: true)"
       << endl;

  return 0;
}
