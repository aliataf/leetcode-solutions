/*
 * Problem: 11. Container With Most Water
 * Link: https://leetcode.com/problems/container-with-most-water/
 * Difficulty: Medium
 *
 * Description:
 * You are given an integer array height of length n. There are n vertical lines
 * drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
 * Find two lines that together with the x-axis form a container, such that the
 * container contains the most water.
 * Return the maximum amount of water a container can store.
 *
 * Example 1:
 * Input: height = [1,8,6,2,5,4,8,3,7]
 * Output: 49
 * Explanation: The vertical lines are [1,8,6,2,5,4,8,3,7]. The max area is between
 * index 1 and 8, which is min(8,7) * (8-1) = 49.
 *
 * Example 2:
 * Input: height = [1,1]
 * Output: 1
 *
 * Constraints:
 * - n == height.length
 * - 2 <= n <= 10^5
 * - 0 <= height[i] <= 10^4
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
     * Approach: Two Pointers
     * Start with widest container (left and right ends).
     * Move the pointer with smaller height inward to potentially find a taller line.
     *
     * Time Complexity: O(n) - single pass with two pointers
     * Space Complexity: O(1) - constant extra space
     */
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int res = 0;
        
        while (l < r) {
            int area = min(height[l], height[r]) * (r - l);
            res = max(res, area);
            
            if (height[l] < height[r]) {
                l++;
            } else {
                r--;
            }
        }
        
        return res;
    }
};

// ============== Test Cases ==============
int main() {
    Solution solution;
    
    // Test Case 1
    vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Test 1: " << solution.maxArea(height1) << endl;  // Expected: 49
    
    // Test Case 2
    vector<int> height2 = {1, 1};
    cout << "Test 2: " << solution.maxArea(height2) << endl;  // Expected: 1
    
    // Test Case 3
    vector<int> height3 = {4, 3, 2, 1, 4};
    cout << "Test 3: " << solution.maxArea(height3) << endl;  // Expected: 16
    
    // Test Case 4
    vector<int> height4 = {1, 2, 1};
    cout << "Test 4: " << solution.maxArea(height4) << endl;  // Expected: 2
    
    cout << "All tests passed!" << endl;
    return 0;
}

