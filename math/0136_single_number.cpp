/*
 * Problem: 136. Single Number
 * Link: https://leetcode.com/problems/single-number/
 * Difficulty: Easy
 *
 * Description:
 * Given a non-empty array of integers nums, every element appears twice except
 * for one. Find that single one.
 *
 * You must implement a solution with a linear runtime complexity and use only
 * constant extra space.
 *
 * Example:
 * Input: nums = [2,2,1]
 * Output: 1
 *
 * Input: nums = [4,1,2,1,2]
 * Output: 4
 *
 * Constraints:
 * - 1 <= nums.length <= 3 * 10^4
 * - -3 * 10^4 <= nums[i] <= 3 * 10^4
 * - Each element in the array appears twice except for one element which
 * appears once.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: XOR Bit Manipulation
   *
   * Key Insight: XOR has these properties:
   * - a ^ a = 0 (same numbers cancel out)
   * - a ^ 0 = a (XOR with 0 returns the number)
   * - XOR is commutative and associative
   *
   * Strategy:
   * XOR all numbers together. Pairs will cancel out, leaving the single number.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(1)
   */
  int singleNumber(vector<int> &nums) {
    int res = 0;
    for (int num : nums) {
      res ^= num;
    }

    return res;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {2, 2, 1};
  cout << "Test 1: " << solution.singleNumber(nums1) << " (Expected: 1)"
       << endl;

  // Test Case 2
  vector<int> nums2 = {4, 1, 2, 1, 2};
  cout << "Test 2: " << solution.singleNumber(nums2) << " (Expected: 4)"
       << endl;

  // Test Case 3
  vector<int> nums3 = {1};
  cout << "Test 3: " << solution.singleNumber(nums3) << " (Expected: 1)"
       << endl;

  return 0;
}
