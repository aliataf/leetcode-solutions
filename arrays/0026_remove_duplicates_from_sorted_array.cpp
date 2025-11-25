/*
 * Problem: 26. Remove Duplicates from Sorted Array
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
 * Difficulty: Easy
 *
 * Description:
 * Given an integer array nums sorted in non-decreasing order, remove the
 * duplicates in-place such that each unique element appears only once. The
 * relative order of the elements should be kept the same. Then return the
 * number of unique elements.
 *
 * Do not allocate extra space for another array; you must do this by modifying
 * the input array in-place with O(1) extra memory.
 *
 * Example:
 * Input: nums = [1,1,2]
 * Output: 2, nums = [1,2,_]
 * Explanation: Your function should return k = 2, with the first two elements
 * of nums being 1 and 2 respectively. It does not matter what you leave beyond
 * the returned k.
 *
 * Constraints:
 * - 1 <= nums.length <= 3 * 10^4
 * - -10^4 <= nums[i] <= 10^4
 * - nums is sorted in non-decreasing order.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Two-pointer (fast-slow)
   * Use 'uniq' as the position to write the next unique element.
   * Iterate through the array; when we find a value greater than the last
   * unique value, we write it to nums[uniq] and increment uniq. This works
   * because the array is sorted.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(1)
   */
  int removeDuplicates(vector<int> &nums) {
    int uniq = 0;
    int curr = INT_MIN; // sentinel smaller than any possible value
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] > curr) {
        curr = nums[i];
        nums[uniq] = nums[i];
        uniq++;
      }
    }
    return uniq;
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
  vector<int> nums1 = {1, 1, 2};
  int k1 = solution.removeDuplicates(nums1);
  cout << "Test 1 k=" << k1 << " array=";
  printArray(nums1, k1);
  // Expected: k=2, array=[1,2]

  // Test Case 2
  vector<int> nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  int k2 = solution.removeDuplicates(nums2);
  cout << "Test 2 k=" << k2 << " array=";
  printArray(nums2, k2);
  // Expected: k=5, array=[0,1,2,3,4]

  // Test Case 3 (no duplicates)
  vector<int> nums3 = {1, 2, 3, 4, 5};
  int k3 = solution.removeDuplicates(nums3);
  cout << "Test 3 k=" << k3 << " array=";
  printArray(nums3, k3);
  // Expected: k=5, array=[1,2,3,4,5]

  return 0;
}
