/*
 * Problem: 137. Single Number II
 * Link: https://leetcode.com/problems/single-number-ii/
 * Difficulty: Medium
 *
 * Description:
 * Given an integer array nums where every element appears three times except
 * for one, which appears exactly once. Find the single element and return it.
 *
 * You must implement a solution with a linear runtime complexity and use only
 * constant extra space.
 *
 * Example:
 * Input: nums = [2,2,3,2]
 * Output: 3
 *
 * Input: nums = [0,1,0,1,0,1,99]
 * Output: 99
 *
 * Constraints:
 * - 1 <= nums.length <= 3 * 10^4
 * - -2^31 <= nums[i] <= 2^31 - 1
 * - Each element in nums appears exactly three times except for one element
 * which appears once.
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Hash Map with Count Tracking
   *
   * Strategy:
   * 1. Use a map to count occurrences of each number.
   * 2. When a number appears once, add it with count 1.
   * 3. When it appears twice, increment count to 2.
   * 4. When it appears three times, remove it from the map.
   * 5. The remaining element in the map is the single number.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(n/3) = O(n)
   */
  int singleNumber(vector<int> &nums) {
    unordered_map<int, int> mp;
    for (int num : nums) {
      if (!mp[num]) {
        mp[num] = 1;
      } else if (mp[num] == 1) {
        mp[num]++;
      } else {
        mp.erase(num);
      }
    }

    return mp.begin()->first;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {2, 2, 3, 2};
  cout << "Test 1: " << solution.singleNumber(nums1) << " (Expected: 3)"
       << endl;

  // Test Case 2
  vector<int> nums2 = {0, 1, 0, 1, 0, 1, 99};
  cout << "Test 2: " << solution.singleNumber(nums2) << " (Expected: 99)"
       << endl;

  return 0;
}
