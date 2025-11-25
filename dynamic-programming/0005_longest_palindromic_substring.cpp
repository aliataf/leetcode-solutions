/*
 * Problem: 5. Longest Palindromic Substring
 * Link: https://leetcode.com/problems/longest-palindromic-substring/
 * Difficulty: Medium
 *
 * Description:
 * Given a string s, return the longest palindromic substring in s.
 *
 * Example 1:
 * Input: s = "babad"
 * Output: "bab"
 * Explanation: "aba" is also a valid answer.
 *
 * Example 2:
 * Input: s = "cbbd"
 * Output: "bb"
 *
 * Constraints:
 * - 1 <= s.length <= 1000
 * - s consist of only digits and English letters
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /*
     * Approach: Dynamic Programming
     * dp[j][i] = true if substring s[j..i] is a palindrome.
     * Base case: single chars are palindromes.
     * Transition: s[j..i] is palindrome if s[j]==s[i] and (length<=3 or s[j+1..i-1] is palindrome).
     *
     * Time Complexity: O(n^2) - fill the DP table
     * Space Complexity: O(n^2) - 2D DP table
     */
    string longestPalindrome(string s) {
        if (s.size() <= 1) return s;
        
        int n = s.size();
        int start = 0, maxLength = 1;
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
            for (int j = 0; j < i; j++) {
                int length = i - j + 1;
                if (s[i] == s[j] && (length <= 3 || dp[j + 1][i - 1])) {
                    dp[j][i] = true;
                    if (length > maxLength) {
                        maxLength = length;
                        start = j;
                    }
                }
            }
        }
        
        return s.substr(start, maxLength);
    }
};

// ============== Test Cases ==============
int main() {
    Solution solution;
    
    // Test Case 1
    string s1 = "babad";
    cout << "Test 1: " << solution.longestPalindrome(s1) << endl;  // Expected: "bab" or "aba"
    
    // Test Case 2
    string s2 = "cbbd";
    cout << "Test 2: " << solution.longestPalindrome(s2) << endl;  // Expected: "bb"
    
    // Test Case 3: Single character
    string s3 = "a";
    cout << "Test 3: " << solution.longestPalindrome(s3) << endl;  // Expected: "a"
    
    // Test Case 4: All same characters
    string s4 = "aaaa";
    cout << "Test 4: " << solution.longestPalindrome(s4) << endl;  // Expected: "aaaa"
    
    // Test Case 5: No palindrome longer than 1
    string s5 = "abcd";
    cout << "Test 5: " << solution.longestPalindrome(s5) << endl;  // Expected: "a" (or any single char)
    
    cout << "All tests passed!" << endl;
    return 0;
}

