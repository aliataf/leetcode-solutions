/*
 * Problem: 35. Search Insert Position
 * Link: https://leetcode.com/problems/search-insert-position/
 * Difficulty: Easy
 *
 * Description:
 * Given a sorted array of distinct integers and a target value, return the
 * index if the target is found. If not, return the index where it would be if
 * it were inserted in order.
 *
 * You must write an algorithm with O(log n) runtime complexity.
 *
 * Example:
 * Input: nums = [1,3,5,6], target = 5
 * Output: 2
 *
 * Input: nums = [1,3,5,6], target = 2
 * Output: 1
 *
 * Input: nums = [1,3,5,6], target = 7
 * Output: 4
 *
 * Constraints:
 * - 1 <= nums.length <= 10^4
 * - -10^4 <= nums[i] <= 10^4
 * - nums contains distinct values sorted in ascending order.
 * - -10^4 <= target <= 10^4
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Binary Search
   * Use binary search to find the target or the position where it should be
   * inserted. Maintain left and right pointers, calculate mid, and adjust based
   * on comparison.
   *
   * Time Complexity: O(log n)
   * Space Complexity: O(1)
   */
  int searchInsert(vector<int> &nums, int target) {
    int left = 0, right = nums.size();
    int index;
    while (left < right) {
      index = (left + right) / 2;
      int node = nums[index];
      if (node == target)
        return index;
      if (target > node) {
        left = index + 1;
      } else {
        right = index;
      }
    }

    return nums[index] < target ? index + 1 : index;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {1, 3, 5, 6};
  int result1 = solution.searchInsert(nums1, 5);
  cout << "Test 1: " << result1 << " (Expected: 2)" << endl;

  // Test Case 2
  vector<int> nums2 = {1, 3, 5, 6};
  int result2 = solution.searchInsert(nums2, 2);
  cout << "Test 2: " << result2 << " (Expected: 1)" << endl;

  // Test Case 3
  vector<int> nums3 = {1, 3, 5, 6};
  int result3 = solution.searchInsert(nums3, 7);
  cout << "Test 3: " << result3 << " (Expected: 4)" << endl;

  return 0;
}
