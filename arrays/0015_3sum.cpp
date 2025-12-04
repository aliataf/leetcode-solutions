/*
 * Problem: 15. 3Sum
 * Link: https://leetcode.com/problems/3sum/
 * Difficulty: Medium
 *
 * Description:
 * Given an integer array nums, return all the triplets [nums[i], nums[j],
 * nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] +
 * nums[k] == 0. Notice that the solution set must not contain duplicate
 * triplets.
 *
 * Example:
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 *
 * Input: nums = [0,1,1]
 * Output: []
 *
 * Input: nums = [0,0,0]
 * Output: [[0,0,0]]
 *
 * Constraints:
 * - 3 <= nums.length <= 3000
 * - -10^5 <= nums[i] <= 10^5
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Sorting + Two Pointers
   * Sort the array first. Iterate through the array with index i.
   * For each i, use two pointers (l and r) to find pairs that sum to -nums[i].
   * Skip duplicates to avoid duplicate triplets.
   *
   * Time Complexity: O(n^2)
   * Space Complexity: O(1) or O(n) depending on sorting implementation
   */
  vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> v;
    sort(nums.begin(), nums.end());
    for (int i = 0, n = nums.size(); i < n; i++) {
      int l = i + 1, r = n - 1;
      if (i > 0 && nums[i] == nums[i - 1]) continue;
      while (l < r) {
        int sum = nums[i] + nums[l] + nums[r];
        if (sum > 0) {
          r--;
        } else if (sum < 0) {
          l++;
        } else {
          v.push_back({nums[i], nums[l], nums[r]});
          l++;
          while (nums[l] == nums[l - 1] && l < r) {
            l++;
          }
        }
      }
    }

    return v;
  }
};

// ============== Test Cases ==============
void printResult(const vector<vector<int>> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    cout << "[";
    for (size_t j = 0; j < result[i].size(); ++j) {
      cout << result[i][j] << (j < result[i].size() - 1 ? "," : "");
    }
    cout << "]" << (i < result.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
  vector<vector<int>> result1 = solution.threeSum(nums1);
  cout << "Test 1: ";
  printResult(result1);
  // Expected: [[-1,-1,2],[-1,0,1]]

  // Test Case 2
  vector<int> nums2 = {0, 1, 1};
  vector<vector<int>> result2 = solution.threeSum(nums2);
  cout << "Test 2: ";
  printResult(result2);
  // Expected: []

  // Test Case 3
  vector<int> nums3 = {0, 0, 0};
  vector<vector<int>> result3 = solution.threeSum(nums3);
  cout << "Test 3: ";
  printResult(result3);
  // Expected: [[0,0,0]]

  return 0;
}
