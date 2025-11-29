/*
 * Problem: 45. Jump Game II
 * Link: https://leetcode.com/problems/jump-game-ii/
 * Difficulty: Medium
 *
 * Description:
 * You are given a 0-indexed array of integers nums of length n. You are
 * initially positioned at nums[0]. Each element nums[i] represents the maximum
 * length of a forward jump from index i. Return the minimum number of jumps to
 * reach nums[n - 1]. The test cases are generated such that you can reach
 * nums[n - 1].
 *
 * Example:
 * Input: nums = [2,3,1,1,4]
 * Output: 2
 * Explanation: The minimum number of jumps to reach the last index is 2.
 * Jump 1 step from index 0 to 1, then 3 steps to the last index.
 *
 * Input: nums = [2,3,0,1,4]
 * Output: 2
 *
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - 0 <= nums[i] <= 1000
 * - It's guaranteed that you can reach nums[n - 1].
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Greedy - BFS-like Level Traversal
   *
   * Key Insight: Think of this as finding the minimum levels in a BFS
   * traversal. Each "level" represents positions reachable with the same number
   * of jumps.
   *
   * Strategy:
   * 1. Track currentEnd: the farthest position reachable with current number of
   * jumps
   * 2. Track maxPosition: the farthest position we can reach from any position
   * seen so far
   * 3. When we reach currentEnd, we must make another jump (increment jumps)
   * 4. Update currentEnd to maxPosition (start exploring the next "level")
   * 5. Stop when currentEnd reaches or exceeds the last index
   *
   * Example: [2,3,1,1,4]
   * - Jump 0: currentEnd=0, can reach indices 0-2, maxPosition=2
   * - Jump 1: currentEnd=2, can reach indices 0-4, maxPosition=4 (done!)
   *
   * Time Complexity: O(n) - single pass through the array
   * Space Complexity: O(1) - only using a few variables
   */
  int jump(vector<int> &nums) {
    int maxPosition = 0, n = nums.size(), jumps = 0, currentEnd = 0;

    if (n == 1) {
      return 0;
    }

    for (int i = 0; i < n; i++) {
      maxPosition = max(maxPosition, i + nums[i]);
      if (i >= currentEnd) {
        currentEnd = maxPosition;
        jumps++;
      }
      if (currentEnd >= n - 1) {
        break;
      }
    }

    return jumps;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {2, 3, 1, 1, 4};
  int result1 = solution.jump(nums1);
  cout << "Test 1: " << result1 << " (Expected: 2)" << endl;

  // Test Case 2
  vector<int> nums2 = {2, 3, 0, 1, 4};
  int result2 = solution.jump(nums2);
  cout << "Test 2: " << result2 << " (Expected: 2)" << endl;

  // Test Case 3
  vector<int> nums3 = {1, 2, 3};
  int result3 = solution.jump(nums3);
  cout << "Test 3: " << result3 << " (Expected: 2)" << endl;

  // Test Case 4
  vector<int> nums4 = {1};
  int result4 = solution.jump(nums4);
  cout << "Test 4: " << result4 << " (Expected: 0)" << endl;

  return 0;
}
