/*
 * Problem: 16. 3Sum Closest
 * Link: https://leetcode.com/problems/3sum-closest/
 * Difficulty: Medium
 *
 * Description:
 * Given an integer array nums of length n and an integer target, find three
 * integers at distinct indices in nums such that the sum is closest to target.
 *
 * Return the sum of the three integers.
 *
 * You may assume that each input would have exactly one solution.
 *
 * Example:
 * Input: nums = [-1,2,1,-4], target = 1
 * Output: 2
 * Explanation: The sum that is closest to the target is 2 (-1 + 2 + 1 = 2).
 *
 * Input: nums = [0,0,0], target = 1
 * Output: 0
 * Explanation: The sum that is closest to the target is 0 (0 + 0 + 0 = 0).
 *
 * Constraints:
 * - 3 <= nums.length <= 500
 * - -1000 <= nums[i] <= 1000
 * - -10^4 <= target <= 10^4
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Sorting + Two Pointers
   *
   * Key Insight: Similar to the 3Sum problem, sorting the array allows us to
   * use two pointers to efficiently find triplets. Since we are looking for the
   * closest sum, we iterate through the array and for each element, we try to
   * find two other elements such that their sum approaches the target.
   *
   * Strategy:
   * 1. Sort the array in ascending order.
   * 2. Iterate through the array with index i from 0 to n-1.
   * 3. For each i, use two pointers, left = i + 1 and right = n - 1.
   * 4. Calculate current sum = nums[i] + nums[left] + nums[right].
   * 5. If abs(target - sum) < abs(target - result), update result.
   * 6. If sum < target, increment left (need larger sum).
   * 7. If sum > target, decrement right (need smaller sum).
   * 8. If sum == target, return sum immediately (distance is 0).
   *
   * Time Complexity: O(N^2) - One loop for i and nested while loop for
   * pointers. Space Complexity: O(log N) or O(N) depending on sort
   * implementation space.
   */
  int threeSumClosest(vector<int> &nums, int target) {
    // Initialize result with the sum of the first three elements
    int result = nums[0] + nums[1] + nums[2];
    sort(nums.begin(), nums.end());

    for (int i = 0, n = nums.size(); i < n - 2; i++) {
      int left = i + 1, right = n - 1;
      while (left < right) {
        int sum = nums[i] + nums[left] + nums[right];

        if (abs(target - sum) < abs(target - result)) {
          result = sum;
        }

        if (sum == target) {
          return target;
        } else if (sum < target) {
          left++;
        } else {
          right--;
        }
      }
    }

    return result;
  }
};

// ============== Test Cases ==============
void runTest(vector<int> nums, int target, int expected) {
  Solution solution;
  cout << "Input: nums = [";
  for (size_t i = 0; i < nums.size(); ++i) {
    cout << nums[i] << (i < nums.size() - 1 ? "," : "");
  }
  cout << "], target = " << target << endl;

  int result = solution.threeSumClosest(nums, target);
  cout << "Output: " << result << endl;
  cout << (result == expected ? "✅ PASSED" : "❌ FAILED") << endl << endl;
}

int main() {
  runTest({-1, 2, 1, -4}, 1, 2);
  runTest({0, 0, 0}, 1, 0);
  runTest({1, 1, 1, 0}, 100, 3);
  runTest({0, 1, 2}, 3, 3);
  runTest({4, 0, 5, -5, 3, 3, 0, -4, -5}, -2, -2);

  return 0;
}
