/*
 * Problem: 1991. Find the Middle Index in Array
 * Link: https://leetcode.com/problems/find-the-middle-index-in-array/
 * Difficulty: Easy
 *
 * Description:
 * Given a 0-indexed integer array nums, find the leftmost middleIndex
 * (i.e., the smallest amongst all the possible ones).
 *
 * A middleIndex is an index where:
 * nums[0] + nums[1] + ... + nums[middleIndex-1] ==
 * nums[middleIndex+1] + nums[middleIndex+2] + ... + nums[nums.length-1]
 *
 * If middleIndex == 0, the left side sum is considered to be 0. Similarly,
 * if middleIndex == nums.length - 1, the right side sum is considered to be 0.
 *
 * Return the leftmost middleIndex that satisfies the condition, or -1 if
 * there is no such index.
 *
 * Example:
 * Input: nums = [2,3,-1,8,4]
 * Output: 3
 * Explanation: The sum of the numbers before index 3 is: 2 + 3 + -1 = 4
 *              The sum of the numbers after index 3 is: 4 = 4
 *
 * Input: nums = [1,-1,4]
 * Output: 2
 * Explanation: The sum before index 2 is: 1 + -1 = 0
 *              The sum after index 2 is: 0
 *
 * Input: nums = [2,5]
 * Output: -1
 * Explanation: There is no valid middleIndex.
 *
 * Constraints:
 * - 1 <= nums.length <= 100
 * - -1000 <= nums[i] <= 1000
 */

#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Prefix Sum with Two Arrays
   *
   * Key Insight: Precompute cumulative sums from both directions, then
   * find the index where left sum equals right sum.
   *
   * Strategy:
   * 1. Build leftSum array: leftSum[i] = sum of elements before index i
   * 2. Build rightSum array: rightSum[i] = sum of elements after index i
   * 3. Find the first index where leftSum[i] == rightSum[i]
   *
   * Time Complexity: O(n) - three passes through the array
   * Space Complexity: O(n) - two auxiliary arrays
   */
  int findMiddleIndex(vector<int> &nums) {
    int n = nums.size();

    if (n == 1) return 0;

    vector<int> leftSum(n, 0);
    vector<int> rightSum(n, 0);

    for (int i = 0; i < n - 1; i++) {
      leftSum[i + 1] = leftSum[i] + nums[i];
    }

    for (int j = n - 1; j > 0; j--) {
      rightSum[j - 1] = rightSum[j] + nums[j];
    }

    for (int i = 0; i < n; i++) {
      if (leftSum[i] == rightSum[i]) {
        return i;
      }
    }

    return -1;
  }

  /*
   * Approach 2: Optimized with Total Sum (Space-efficient)
   *
   * Key Insight: Instead of storing both prefix arrays, use the relationship:
   * rightSum = totalSum - leftSum - nums[i]
   *
   * At middle index: leftSum == rightSum
   * So: leftSum == totalSum - leftSum - nums[i]
   * Which means: 2 * leftSum + nums[i] == totalSum
   *
   * Time Complexity: O(n) - two passes through the array
   * Space Complexity: O(1) - only constant extra space
   */
  int findMiddleIndexOptimized(vector<int> &nums) {
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    int leftSum = 0;

    for (int i = 0; i < nums.size(); i++) {
      // Check if left sum equals right sum
      // rightSum = totalSum - leftSum - nums[i]
      if (leftSum == totalSum - leftSum - nums[i]) {
        return i;
      }
      leftSum += nums[i];
    }

    return -1;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  cout << "=== Approach 1: Prefix Sum with Two Arrays ===" << endl;

  // Test Case 1
  vector<int> nums1 = {2, 3, -1, 8, 4};
  cout << "Test 1: [2,3,-1,8,4] -> " << solution.findMiddleIndex(nums1) << endl;
  // Expected: 3

  // Test Case 2
  vector<int> nums2 = {1, -1, 4};
  cout << "Test 2: [1,-1,4] -> " << solution.findMiddleIndex(nums2) << endl;
  // Expected: 2

  // Test Case 3
  vector<int> nums3 = {2, 5};
  cout << "Test 3: [2,5] -> " << solution.findMiddleIndex(nums3) << endl;
  // Expected: -1

  // Test Case 4: Single element
  vector<int> nums4 = {1};
  cout << "Test 4: [1] -> " << solution.findMiddleIndex(nums4) << endl;
  // Expected: 0

  cout << endl << "=== Approach 2: Optimized (O(1) space) ===" << endl;

  // Test Case 5
  vector<int> nums5 = {2, 3, -1, 8, 4};
  cout << "Test 5: [2,3,-1,8,4] -> " << solution.findMiddleIndexOptimized(nums5)
       << endl;
  // Expected: 3

  // Test Case 6
  vector<int> nums6 = {1, -1, 4};
  cout << "Test 6: [1,-1,4] -> " << solution.findMiddleIndexOptimized(nums6)
       << endl;
  // Expected: 2

  // Test Case 7: Middle index at 0
  vector<int> nums7 = {0, 0, 0, 0};
  cout << "Test 7: [0,0,0,0] -> " << solution.findMiddleIndexOptimized(nums7)
       << endl;
  // Expected: 0

  return 0;
}
