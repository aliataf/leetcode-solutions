/*
 * Problem: 75. Sort Colors
 * Link: https://leetcode.com/problems/sort-colors/
 * Difficulty: Medium
 *
 * Description:
 * Given an array nums with n objects colored red, white, or blue, sort them
 * in-place so that objects of the same color are adjacent, with the colors
 * in the order red, white, and blue.
 *
 * We will use the integers 0, 1, and 2 to represent the color red, white,
 * and blue, respectively.
 *
 * You must solve this problem without using the library's sort function.
 *
 * Example:
 * Input: nums = [2,0,2,1,1,0]
 * Output: [0,0,1,1,2,2]
 *
 * Input: nums = [2,0,1]
 * Output: [0,1,2]
 *
 * Constraints:
 * - n == nums.length
 * - 1 <= n <= 300
 * - nums[i] is either 0, 1, or 2.
 *
 * Follow up: Could you come up with a one-pass algorithm using only constant
 * extra space?
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Counting Sort (Two-pass)
   *
   * Key Insight: Since we only have three distinct values (0, 1, 2), we can
   * count the occurrences of each and then overwrite the array.
   *
   * Strategy:
   * 1. First pass: Count occurrences of 0s (red), 1s (white), and 2s (blue)
   * 2. Second pass: Overwrite the array based on counts
   *    - Fill with 0s while redCount > 0
   *    - Fill with 1s while whiteCount > 0
   *    - Fill with 2s for the rest
   *
   * The implementation uses a clever ternary expression to determine the
   * value at each position by decrementing counters.
   *
   * Time Complexity: O(n) - two passes through the array
   * Space Complexity: O(1) - only three counter variables
   */
  void sortColors(vector<int> &nums) {
    int redCount = 0, whiteCount = 0, blueCount = 0;
    for (int num : nums) {
      redCount += (num == 0);
      whiteCount += (num == 1);
      blueCount += (num == 2);
    }
    for (int i = 0, n = nums.size(); i < n; i++) {
      nums[i] = (redCount--) > 0 ? 0 : ((whiteCount--) > 0 ? 1 : 2);
    }
  }

  /*
   * Approach 2: Dutch National Flag Algorithm (One-pass) - Follow-up Solution
   *
   * Key Insight: Use three pointers to partition the array in a single pass.
   * This is the famous algorithm by Edsger Dijkstra.
   *
   * Strategy:
   * - low: boundary for 0s (all elements before low are 0)
   * - mid: current element being examined
   * - high: boundary for 2s (all elements after high are 2)
   *
   * Invariants maintained:
   * - [0, low): all 0s (red)
   * - [low, mid): all 1s (white)
   * - [mid, high]: unprocessed elements
   * - (high, n): all 2s (blue)
   *
   * Process:
   * - If nums[mid] == 0: swap with nums[low], increment both low and mid
   * - If nums[mid] == 1: just increment mid (it's in the right place)
   * - If nums[mid] == 2: swap with nums[high], decrement high (don't increment
   *   mid because the swapped element needs to be examined)
   *
   * Time Complexity: O(n) - single pass through the array
   * Space Complexity: O(1) - only three pointer variables
   */
  void sortColorsOnePass(vector<int> &nums) {
    int low = 0, mid = 0, high = nums.size() - 1;

    while (mid <= high) {
      if (nums[mid] == 0) {
        swap(nums[low], nums[mid]);
        low++;
        mid++;
      } else if (nums[mid] == 1) {
        mid++;
      } else { // nums[mid] == 2
        swap(nums[mid], nums[high]);
        high--;
        // Don't increment mid, need to examine the swapped element
      }
    }
  }
};

// ============== Test Cases ==============
void printArray(const vector<int> &arr) {
  cout << "[";
  for (size_t i = 0; i < arr.size(); ++i) {
    cout << arr[i];
    if (i < arr.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  cout << "=== Approach 1: Counting Sort (Two-pass) ===" << endl;

  // Test Case 1
  vector<int> nums1 = {2, 0, 2, 1, 1, 0};
  cout << "Test 1 Before: ";
  printArray(nums1);
  solution.sortColors(nums1);
  cout << "Test 1 After:  ";
  printArray(nums1);
  // Expected: [0,0,1,1,2,2]

  // Test Case 2
  vector<int> nums2 = {2, 0, 1};
  cout << "Test 2 Before: ";
  printArray(nums2);
  solution.sortColors(nums2);
  cout << "Test 2 After:  ";
  printArray(nums2);
  // Expected: [0,1,2]

  // Test Case 3: All same color
  vector<int> nums3 = {1, 1, 1};
  cout << "Test 3 Before: ";
  printArray(nums3);
  solution.sortColors(nums3);
  cout << "Test 3 After:  ";
  printArray(nums3);
  // Expected: [1,1,1]

  cout << endl << "=== Approach 2: Dutch National Flag (One-pass) ===" << endl;

  // Test Case 4: One-pass version
  vector<int> nums4 = {2, 0, 2, 1, 1, 0};
  cout << "Test 4 Before: ";
  printArray(nums4);
  solution.sortColorsOnePass(nums4);
  cout << "Test 4 After:  ";
  printArray(nums4);
  // Expected: [0,0,1,1,2,2]

  // Test Case 5: One-pass with different input
  vector<int> nums5 = {2, 0, 1};
  cout << "Test 5 Before: ";
  printArray(nums5);
  solution.sortColorsOnePass(nums5);
  cout << "Test 5 After:  ";
  printArray(nums5);
  // Expected: [0,1,2]

  // Test Case 6: Reverse sorted - one-pass
  vector<int> nums6 = {2, 2, 1, 1, 0, 0};
  cout << "Test 6 Before: ";
  printArray(nums6);
  solution.sortColorsOnePass(nums6);
  cout << "Test 6 After:  ";
  printArray(nums6);
  // Expected: [0,0,1,1,2,2]

  // Test Case 7: Single element
  vector<int> nums7 = {0};
  cout << "Test 7 Before: ";
  printArray(nums7);
  solution.sortColorsOnePass(nums7);
  cout << "Test 7 After:  ";
  printArray(nums7);
  // Expected: [0]

  return 0;
}
