/*
 * Problem: 128. Longest Consecutive Sequence
 * Link: https://leetcode.com/problems/longest-consecutive-sequence/
 * Difficulty: Medium
 *
 * Description:
 * Given an unsorted array of integers nums, return the length of the longest
 * consecutive elements sequence. You must write an algorithm that runs in O(n)
 * time.
 *
 * Example:
 * Input: nums = [100,4,200,1,3,2]
 * Output: 4
 * Explanation: The longest consecutive elements sequence is [1, 2, 3, 4].
 * Length is 4.
 *
 * Input: nums = [0,3,7,2,5,8,4,6,0,1]
 * Output: 9
 *
 * Constraints:
 * - 0 <= nums.length <= 10^5
 * - -10^9 <= nums[i] <= 10^9
 */

#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Hash Set
   *
   * Strategy:
   * 1. Insert all numbers into a hash set for O(1) lookups.
   * 2. For each number, check if it's the start of a sequence (n-1 not in set).
   * 3. If it's a start, count consecutive numbers (n+1, n+2, ...) in the set.
   * 4. Track the maximum sequence length found.
   *
   * Time Complexity: O(n) - each number is visited at most twice
   * Space Complexity: O(n) - for the hash set
   */
  int longestConsecutive(vector<int> &nums) {
    unordered_set<int> numSet(nums.begin(), nums.end());
    int longest = 0;
    for (auto &num : numSet) {
      // if this is the start of the sequence
      if (!numSet.count(num - 1)) {
        int length = 1;
        while (numSet.count(num + length)) ++length;
        longest = max(longest, length);
      }
    }
    return longest;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1 = {100, 4, 200, 1, 3, 2};
  cout << "Test 1: " << solution.longestConsecutive(nums1) << " (Expected: 4)"
       << endl;

  // Test Case 2
  vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
  cout << "Test 2: " << solution.longestConsecutive(nums2) << " (Expected: 9)"
       << endl;

  // Test Case 3
  vector<int> nums3 = {};
  cout << "Test 3: " << solution.longestConsecutive(nums3) << " (Expected: 0)"
       << endl;

  return 0;
}
