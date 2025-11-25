/*
 * Problem: 4. Median of Two Sorted Arrays
 * Link: https://leetcode.com/problems/median-of-two-sorted-arrays/
 * Difficulty: Hard
 *
 * Description:
 * Given two sorted arrays nums1 and nums2 of size m and n respectively,
 * return the median of the two sorted arrays.
 * The overall run time complexity should be O(log (m+n)).
 *
 * Example 1:
 * Input: nums1 = [1,3], nums2 = [2]
 * Output: 2.00000
 * Explanation: merged array = [1,2,3] and median is 2.
 *
 * Example 2:
 * Input: nums1 = [1,2], nums2 = [3,4]
 * Output: 2.50000
 * Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
 *
 * Constraints:
 * - nums1.length == m
 * - nums2.length == n
 * - 0 <= m <= 1000
 * - 0 <= n <= 1000
 * - 1 <= m + n <= 2000
 * - -10^6 <= nums1[i], nums2[i] <= 10^6
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    /*
     * Approach: Binary Search on Partition
     * Binary search on the shorter array to find the correct partition point.
     * Partition both arrays such that left halves combined equal right halves.
     * Valid partition: max(left) <= min(right) for both arrays cross-wise.
     *
     * Time Complexity: O(log(min(m, n))) - binary search on shorter array
     * Space Complexity: O(1) - constant extra space
     */
    double findMedianSortedArrays(vector<int>& a1, vector<int>& a2) {
        if (a1.size() > a2.size()) swap(a1, a2);  // make sure a1 is shorter
        
        int n1 = a1.size(), n2 = a2.size();
        
        // range of a1 cut location: n1 means no right half for a1
        int lo = 0, hi = n1;
        while (lo <= hi) {
            int cut1 = (lo + hi) / 2;  // cut location is counted to right half
            int cut2 = (n1 + n2) / 2 - cut1;
            
            int l1 = cut1 == 0 ? INT_MIN : a1[cut1 - 1];
            int l2 = cut2 == 0 ? INT_MIN : a2[cut2 - 1];
            int r1 = cut1 == n1 ? INT_MAX : a1[cut1];
            int r2 = cut2 == n2 ? INT_MAX : a2[cut2];
            
            if (l1 > r2) hi = cut1 - 1;
            else if (l2 > r1) lo = cut1 + 1;
            else return (n1 + n2) % 2 ? min(r1, r2) : (max(l1, l2) + min(r1, r2)) / 2.;
        }
        
        return -1;
    }
};

// ============== Test Cases ==============
int main() {
    Solution solution;
    
    // Test Case 1
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    cout << "Test 1: " << solution.findMedianSortedArrays(nums1, nums2) << endl;  // Expected: 2.0
    
    // Test Case 2
    vector<int> nums3 = {1, 2};
    vector<int> nums4 = {3, 4};
    cout << "Test 2: " << solution.findMedianSortedArrays(nums3, nums4) << endl;  // Expected: 2.5
    
    // Test Case 3: One empty array
    vector<int> nums5 = {};
    vector<int> nums6 = {1};
    cout << "Test 3: " << solution.findMedianSortedArrays(nums5, nums6) << endl;  // Expected: 1.0
    
    // Test Case 4
    vector<int> nums7 = {1, 2, 3, 4, 5};
    vector<int> nums8 = {6, 7, 8, 9, 10};
    cout << "Test 4: " << solution.findMedianSortedArrays(nums7, nums8) << endl;  // Expected: 5.5
    
    cout << "All tests passed!" << endl;
    return 0;
}

