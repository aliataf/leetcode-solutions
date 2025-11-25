/*
 * Problem: 27. Remove Element
 * Link: https://leetcode.com/problems/remove-element/
 * Difficulty: Easy
 *
 * Description:
 * Given an integer array nums and an integer val, remove all occurrences of val
 * in nums in-place. The order of the elements can be changed. After removal,
 * return the new length k. Elements beyond the first k elements are not
 * important.
 *
 * Example:
 * Input: nums = [3,2,2,3], val = 3
 * Output: k = 2, nums = [2,2,_,_]
 * Explanation: Your function should return k = 2, with the first two elements
 * of nums being 2.
 *
 * Constraints:
 * - 0 <= nums.length <= 100
 * - 0 <= nums[i] <= 50
 * - 0 <= val <= 100
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Two-pointer (fast-slow)
   * Use 'k' as the position to write the next element that is not equal to val.
   * Iterate through the array; when nums[i] != val, copy it to nums[k] and
   * increment k. This works in O(n) time and O(1) extra space.
   */
  int removeElement(vector<int> &nums, int val) {
    int k = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] != val) {
        nums[k++] = nums[i];
      }
    }
    return k;
  }
};

// ============== Test Cases ==============
void printArray(const vector<int> &arr, int k) {
  cout << "[";
  for (int i = 0; i < k; ++i) {
    cout << arr[i] << (i < k - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {3, 2, 2, 3};
  int k1 = solution.removeElement(nums1, 3);
  cout << "Test 1 k=" << k1 << " array=";
  printArray(nums1, k1);
  // Expected: k=2, array=[2,2]

  // Test Case 2
  vector<int> nums2 = {0, 1, 2, 2, 3, 0, 4, 2};
  int k2 = solution.removeElement(nums2, 2);
  cout << "Test 2 k=" << k2 << " array=";
  printArray(nums2, k2);
  // Expected: k=5, array contains [0,1,3,0,4] in any order

  // Test Case 3 (no removal)
  vector<int> nums3 = {1, 2, 3};
  int k3 = solution.removeElement(nums3, 5);
  cout << "Test 3 k=" << k3 << " array=";
  printArray(nums3, k3);
  // Expected: k=3, array=[1,2,3]

  return 0;
}
