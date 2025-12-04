/*
 * Problem: 88. Merge Sorted Array
 * Link: https://leetcode.com/problems/merge-sorted-array/
 * Difficulty: Easy
 *
 * Description:
 * You are given two integer arrays nums1 and nums2, sorted in non-decreasing
 * order, and two integers m and n, representing the number of elements in nums1
 * and nums2 respectively. Merge nums1 and nums2 into a single array sorted in
 * non-decreasing order. The final sorted array should not be returned by the
 * function, but instead be stored inside the array nums1. To accommodate this,
 * nums1 has a length of m + n, where the first m elements denote the elements
 * that should be merged, and the last n elements are set to 0 and should be
 * ignored. nums2 has a length of n.
 *
 * Example:
 * Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
 * Output: [1,2,2,3,5,6]
 * Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
 * The result of the merge is [1,2,2,3,5,6] with the underlined elements coming
 * from nums1.
 *
 * Input: nums1 = [1], m = 1, nums2 = [], n = 0
 * Output: [1]
 *
 * Input: nums1 = [0], m = 0, nums2 = [1], n = 1
 * Output: [1]
 *
 * Constraints:
 * - nums1.length == m + n
 * - nums2.length == n
 * - 0 <= m, n <= 200
 * - 1 <= m + n <= 200
 * - -10^9 <= nums1[i], nums2[j] <= 10^9
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Two Pointers (Reverse)
   *
   * Strategy:
   * 1. Use three pointers:
   *    - `m`: points to the last valid element in nums1 (initially m-1)
   *    - `n`: points to the last element in nums2 (initially n-1)
   *    - `i`: points to the last position in nums1 (initially m+n-1)
   * 2. Iterate backwards from the end of nums1.
   * 3. Compare elements at `nums1[m]` and `nums2[n]`.
   * 4. Place the larger element at `nums1[i]` and decrement the corresponding
   * pointer.
   * 5. If one array is exhausted, copy the remaining elements from the other
   * array.
   *
   * Time Complexity: O(m + n)
   * Space Complexity: O(1)
   */
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int i = m + n - 1;
    m--;
    n--;
    while (i >= 0) {
      if (m < 0) {
        nums1[i--] = nums2[n--];
      } else if (n < 0) {
        nums1[i--] = nums1[m--];
      } else if (nums1[m] >= nums2[n]) {
        nums1[i--] = nums1[m--];
      } else {
        nums1[i--] = nums2[n--];
      }
    }
  }
};

// ============== Test Cases ==============
void printVector(const vector<int> &v) {
  cout << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i];
    if (i < v.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  vector<int> nums1_1 = {1, 2, 3, 0, 0, 0};
  int m1 = 3;
  vector<int> nums2_1 = {2, 5, 6};
  int n1 = 3;
  solution.merge(nums1_1, m1, nums2_1, n1);
  cout << "Test 1: ";
  printVector(nums1_1);
  // Expected: [1,2,2,3,5,6]

  // Test Case 2
  vector<int> nums1_2 = {1};
  int m2 = 1;
  vector<int> nums2_2 = {};
  int n2 = 0;
  solution.merge(nums1_2, m2, nums2_2, n2);
  cout << "Test 2: ";
  printVector(nums1_2);
  // Expected: [1]

  // Test Case 3
  vector<int> nums1_3 = {0};
  int m3 = 0;
  vector<int> nums2_3 = {1};
  int n3 = 1;
  solution.merge(nums1_3, m3, nums2_3, n3);
  cout << "Test 3: ";
  printVector(nums1_3);
  // Expected: [1]

  return 0;
}
