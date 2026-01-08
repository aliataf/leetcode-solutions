/*
 * Problem: 228. Summary Ranges
 * Link: https://leetcode.com/problems/summary-ranges/
 * Difficulty: Easy
 *
 * Description:
 * You are given a sorted unique integer array nums.
 *
 * A range [a,b] is the set of all integers from a to b (inclusive).
 *
 * Return the smallest sorted list of ranges that cover all the numbers in the
 * array exactly. That is, each element of nums is covered by exactly one of
 * the ranges, and there is no integer x such that x is in one of the ranges
 * but not in nums.
 *
 * Each range [a,b] in the list should be output as:
 * - "a->b" if a != b
 * - "a" if a == b
 *
 * Example:
 * Input: nums = [0,1,2,4,5,7]
 * Output: ["0->2","4->5","7"]
 * Explanation: The ranges are:
 * [0,2] --> "0->2"
 * [4,5] --> "4->5"
 * [7,7] --> "7"
 *
 * Input: nums = [0,2,3,4,6,8,9]
 * Output: ["0","2->4","6","8->9"]
 *
 * Constraints:
 * - 0 <= nums.length <= 20
 * - -2^31 <= nums[i] <= 2^31 - 1
 * - All the values of nums are unique.
 * - nums is sorted in ascending order.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Linear Scan with Range Tracking
   *
   * Key Insight: Since the array is sorted and contains unique elements,
   * consecutive numbers differ by exactly 1. We track the start and end
   * of each range, extending the range when we find consecutive numbers.
   *
   * Strategy:
   * 1. Handle empty array edge case
   * 2. Initialize start and end pointers to the first element
   * 3. For each subsequent element:
   *    - If it's consecutive (nums[i] == end + 1), extend the range (update
   * end)
   *    - Otherwise, close the current range and start a new one
   * 4. After the loop, don't forget to add the last range
   *
   * Time Complexity: O(n) - single pass through the array
   * Space Complexity: O(1) - excluding the output array
   */
  vector<string> summaryRanges(vector<int> &nums) {
    vector<string> res;
    if (nums.empty()) return res;

    int start = nums[0], end = nums[0];
    for (int i = 1; i < nums.size(); i++) {
      if (nums[i] == end + 1) {
        end = nums[i];
      } else {
        if (start == end) res.push_back(to_string(start));
        else res.push_back(to_string(start) + "->" + to_string(end));
        start = end = nums[i];
      }
    }

    if (start == end) res.push_back(to_string(start));
    else res.push_back(to_string(start) + "->" + to_string(end));

    return res;
  }
};

// ============== Test Cases ==============
void printResult(const vector<string> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    cout << "\"" << result[i] << "\"";
    if (i < result.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {0, 1, 2, 4, 5, 7};
  cout << "Test 1: [0,1,2,4,5,7] -> ";
  printResult(solution.summaryRanges(nums1));
  // Expected: ["0->2","4->5","7"]

  // Test Case 2
  vector<int> nums2 = {0, 2, 3, 4, 6, 8, 9};
  cout << "Test 2: [0,2,3,4,6,8,9] -> ";
  printResult(solution.summaryRanges(nums2));
  // Expected: ["0","2->4","6","8->9"]

  // Test Case 3: Empty array
  vector<int> nums3 = {};
  cout << "Test 3: [] -> ";
  printResult(solution.summaryRanges(nums3));
  // Expected: []

  // Test Case 4: Single element
  vector<int> nums4 = {5};
  cout << "Test 4: [5] -> ";
  printResult(solution.summaryRanges(nums4));
  // Expected: ["5"]

  // Test Case 5: All consecutive
  vector<int> nums5 = {1, 2, 3, 4, 5};
  cout << "Test 5: [1,2,3,4,5] -> ";
  printResult(solution.summaryRanges(nums5));
  // Expected: ["1->5"]

  // Test Case 6: No consecutive
  vector<int> nums6 = {1, 3, 5, 7};
  cout << "Test 6: [1,3,5,7] -> ";
  printResult(solution.summaryRanges(nums6));
  // Expected: ["1","3","5","7"]

  return 0;
}
