/*
 * Problem: 198. House Robber
 * Link: https://leetcode.com/problems/house-robber/
 * Difficulty: Medium
 *
 * Description:
 * You are a professional robber planning to rob houses along a street. Each
 * house has a certain amount of money stashed, the only constraint stopping
 * you from robbing each of them is that adjacent houses have security systems
 * connected and it will automatically contact the police if two adjacent
 * houses were broken into on the same night.
 *
 * Given an integer array nums representing the amount of money of each house,
 * return the maximum amount of money you can rob tonight without alerting the
 * police.
 *
 * Example 1:
 * Input: nums = [1,2,3,1]
 * Output: 4
 * Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
 * Total amount you can rob = 1 + 3 = 4.
 *
 * Example 2:
 * Input: nums = [2,7,9,3,1]
 * Output: 12
 * Explanation: Rob house 1, house 3, and house 5: 2 + 9 + 1 = 12.
 *
 * Constraints:
 * - 1 <= nums.length <= 100
 * - 0 <= nums[i] <= 400
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Dynamic Programming with O(1) Space
   *
   * Key Insight: At each house, we have two choices:
   * 1. Rob this house: total = (best up to i-2) + nums[i]
   * 2. Skip this house: total = (best up to i-1)
   * The answer is the max of these two: dp[i] = max(dp[i-1], dp[i-2] + nums[i]).
   * Since dp[i] only depends on the previous two values, we can collapse the
   * table to two rolling variables.
   *
   * Strategy:
   * 1. Track `curr` (best up to the previous house) and `prev` (best up to two
   *    houses ago). Both start at 0 (empty prefix).
   * 2. For each house, compute `take = prev + money` (rob this house).
   * 3. Shift: prev becomes the old curr, curr becomes max(take, curr) — i.e.,
   *    the better of robbing this house vs. skipping it.
   * 4. After the loop, curr holds the answer.
   *
   * Time Complexity: O(n) - single pass over the array.
   * Space Complexity: O(1) - only two integers tracked.
   */
  int rob(vector<int> &nums) {
    int curr = 0, prev = 0;
    for (auto money : nums) {
      int take = prev + money;
      prev = curr;
      curr = max(take, curr);
    }
    return curr;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  vector<int> nums1 = {1, 2, 3, 1};
  cout << "Test 1: " << solution.rob(nums1) << " (Expected: 4)" << endl;

  vector<int> nums2 = {2, 7, 9, 3, 1};
  cout << "Test 2: " << solution.rob(nums2) << " (Expected: 12)" << endl;

  vector<int> nums3 = {5};
  cout << "Test 3: " << solution.rob(nums3) << " (Expected: 5)" << endl;

  vector<int> nums4 = {2, 1};
  cout << "Test 4: " << solution.rob(nums4) << " (Expected: 2)" << endl;

  vector<int> nums5 = {2, 1, 1, 2};
  cout << "Test 5: " << solution.rob(nums5) << " (Expected: 4)" << endl;

  vector<int> nums6 = {0, 0, 0};
  cout << "Test 6: " << solution.rob(nums6) << " (Expected: 0)" << endl;

  return 0;
}
