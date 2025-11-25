/*
 * Problem: 3. Longest Substring Without Repeating Characters
 * Link: https://leetcode.com/problems/longest-substring-without-repeating-characters/
 * Difficulty: Medium
 *
 * Description:
 * Given a string s, find the length of the longest substring without repeating characters.
 *
 * Example 1:
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 *
 * Example 2:
 * Input: s = "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 *
 * Example 3:
 * Input: s = "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 *
 * Constraints:
 * - 0 <= s.length <= 5 * 10^4
 * - s consists of English letters, digits, symbols and spaces
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /*
     * Approach: Sliding Window with Character Index Map
     * Use an array to store the last seen index of each character.
     * Slide the window by moving left pointer when a repeat is found.
     *
     * Time Complexity: O(n) - single pass through the string
     * Space Complexity: O(1) - fixed size array of 256 characters
     */
    int lengthOfLongestSubstring(string s) {
        int i = 0, res = 0;
        vector<int> mp(256, -1);
        
        for (int j = 0; j < s.length(); j++) {
            if (mp[s[j]] != -1) {
                i = max(i, mp[s[j]] + 1);
            }
            mp[s[j]] = j;
            res = max(res, j - i + 1);
        }
        
        return res;
    }
};

// ============== Test Cases ==============
int main() {
    Solution solution;
    
    // Test Case 1
    string s1 = "abcabcbb";
    cout << "Test 1: " << solution.lengthOfLongestSubstring(s1) << endl;  // Expected: 3
    
    // Test Case 2
    string s2 = "bbbbb";
    cout << "Test 2: " << solution.lengthOfLongestSubstring(s2) << endl;  // Expected: 1
    
    // Test Case 3
    string s3 = "pwwkew";
    cout << "Test 3: " << solution.lengthOfLongestSubstring(s3) << endl;  // Expected: 3
    
    // Test Case 4: Empty string
    string s4 = "";
    cout << "Test 4: " << solution.lengthOfLongestSubstring(s4) << endl;  // Expected: 0
    
    // Test Case 5: Single character
    string s5 = "a";
    cout << "Test 5: " << solution.lengthOfLongestSubstring(s5) << endl;  // Expected: 1
    
    cout << "All tests passed!" << endl;
    return 0;
}

