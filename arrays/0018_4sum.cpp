/*
 * Problem: 18. 4Sum
 * Link: https://leetcode.com/problems/4sum/
 * Difficulty: Medium
 *
 * Description:
 * Given an array nums of n integers, return an array of all the unique
 * quadruplets [nums[a], nums[b], nums[c], nums[d]] such that: 0 <= a, b, c, d <
 * n a, b, c, and d are distinct. nums[a] + nums[b] + nums[c] + nums[d] ==
 * target
 *
 * You may return the answer in any order.
 *
 * Example:
 * Input: nums = [1,0,-1,0,-2,2], target = 0
 * Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 *
 * Input: nums = [2,2,2,2,2], target = 8
 * Output: [[2,2,2,2]]
 *
 * Constraints:
 * - 1 <= nums.length <= 200
 * - -10^9 <= nums[i] <= 10^9
 * - -10^9 <= target <= 10^9
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long int lli;

class Solution {
public:
  /*
   * Approach: Sorting + Two Pointers (Extension of 3Sum)
   *
   * Key Insight: Sorting the array allows for efficient two-pointer traversal
   * to find pairs that sum to a specific value. 4Sum can be reduced to 3Sum,
   * which reduces to 2Sum by fixing one number at a time.
   *
   * Strategy:
   * 1. Sort the array.
   * 2. Iterate through the array with index i (first number).
   * 3. Iterate with index j > i (second number).
   * 4. Use two pointers (left, right) for the remaining elements to find
   *    pairs that sum to (target - nums[i] - nums[j]).
   * 5. Skip duplicates carefully at every level (i, j, left, right) to ensure
   *    unique quadruplets.
   * 6. Use long long to prevent integer overflow during sum calculation.
   *
   * Time Complexity: O(N^3)
   * Space Complexity: O(log N) or O(N) for sorting.
   */
  vector<vector<int>> fourSum(vector<int> &nums, int target) {
    vector<vector<int>> result;
    int n = nums.size();
    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 3; i++) {
      if (i > 0 && nums[i] == nums[i - 1]) continue;

      for (int j = i + 1; j < n; j++) {
        if (j > i + 1 && nums[j] == nums[j - 1]) continue;

        int left = j + 1, right = n - 1;

        while (left < right) {
          lli sum = (lli)nums[i] + nums[j] + nums[left] + nums[right];

          if (sum == (lli)target) {
            result.push_back({nums[i], nums[j], nums[left], nums[right]});
            left++;
            right--;
            while (left < right && nums[left] == nums[left - 1]) left++;
            while (left < right && nums[right] == nums[right + 1]) right--;
          } else if (sum < target) left++;
          else right--;
        }
      }
    }

    return result;
  }
};

// ============== Test Cases ==============
void runTest(vector<int> nums, int target, vector<vector<int>> expected) {
  Solution solution;
  cout << "Input: nums = [";
  for (size_t i = 0; i < nums.size(); ++i) {
    cout << nums[i] << (i < nums.size() - 1 ? "," : "");
  }
  cout << "], target = " << target << endl;

  vector<vector<int>> result = solution.fourSum(nums, target);

  // Sort result and expected for comparison
  for (auto &vec : result) sort(vec.begin(), vec.end());
  sort(result.begin(), result.end());
  for (auto &vec : expected) sort(vec.begin(), vec.end());
  sort(expected.begin(), expected.end());

  if (result == expected) {
    cout << "✅ PASSED" << endl;
  } else {
    cout << "❌ FAILED" << endl;
    cout << "Expected: [";
    for (const auto &vec : expected) {
      cout << "[";
      for (size_t i = 0; i < vec.size(); ++i)
        cout << vec[i] << (i < vec.size() - 1 ? "," : "");
      cout << "]";
    }
    cout << "]" << endl;
    cout << "Got: [";
    for (const auto &vec : result) {
      cout << "[";
      for (size_t i = 0; i < vec.size(); ++i)
        cout << vec[i] << (i < vec.size() - 1 ? "," : "");
      cout << "]";
    }
    cout << "]" << endl;
  }
  cout << endl;
}

int main() {
  runTest({1, 0, -1, 0, -2, 2}, 0,
          {{-2, -1, 1, 2}, {-2, 0, 0, 2}, {-1, 0, 0, 1}});
  runTest({2, 2, 2, 2, 2}, 8, {{2, 2, 2, 2}});
  runTest({1000000000, 1000000000, 1000000000, 1000000000}, -294967296,
          {}); // Overflow test

  return 0;
}
