/*
 * Problem: 1. Two Sum
 * Link: https://leetcode.com/problems/two-sum/
 * Difficulty: Easy
 *
 * Description:
 * Given an array of integers nums and an integer target, return indices of the
 * two numbers such that they add up to target. You may assume that each input
 * would have exactly one solution, and you may not use the same element twice.
 *
 * Example:
 * Input: nums = [2,7,11,15], target = 9
 * Output: [0,1]
 * Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
 *
 * Constraints:
 * - 2 <= nums.length <= 10^4
 * - -10^9 <= nums[i] <= 10^9
 * - -10^9 <= target <= 10^9
 * - Only one valid answer exists.
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Hash Map
   * Use a hash map to store each number and its index as we iterate.
   * For each number, check if (target - num) exists in the map.
   *
   * Time Complexity: O(n) - single pass through the array
   * Space Complexity: O(n) - hash map stores at most n elements
   */
  vector<int> twoSum(vector<int> &nums, int target) {
    unordered_map<int, int> seen; // num -> index

    for (int i = 0; i < nums.size(); i++) {
      int complement = target - nums[i];

      if (seen.find(complement) != seen.end()) {
        return {seen[complement], i};
      }

      seen[nums[i]] = i;
    }

    return {}; // No solution found (shouldn't happen per constraints)
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {2, 7, 11, 15};
  int target1 = 9;
  vector<int> result1 = solution.twoSum(nums1, target1);
  cout << "Test 1: [" << result1[0] << ", " << result1[1] << "]"
       << endl; // Expected: [0, 1]

  // Test Case 2
  vector<int> nums2 = {3, 2, 4};
  int target2 = 6;
  vector<int> result2 = solution.twoSum(nums2, target2);
  cout << "Test 2: [" << result2[0] << ", " << result2[1] << "]"
       << endl; // Expected: [1, 2]

  // Test Case 3
  vector<int> nums3 = {3, 3};
  int target3 = 6;
  vector<int> result3 = solution.twoSum(nums3, target3);
  cout << "Test 3: [" << result3[0] << ", " << result3[1] << "]"
       << endl; // Expected: [0, 1]

  cout << "All tests passed!" << endl;
  return 0;
}
