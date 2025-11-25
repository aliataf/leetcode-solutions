/*
 * Problem: 28. Find the Index of the First Occurrence in a String
 * Link:
 * https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/
 * Difficulty: Easy
 *
 * Description:
 * Given two strings needle and haystack, return the index of the first
 * occurrence of needle in haystack, or -1 if needle is not part of haystack.
 *
 * Example:
 * Input: haystack = "sadbutsad", needle = "sad"
 * Output: 0
 *
 * Input: haystack = "leetcode", needle = "leeto"
 * Output: -1
 *
 * Constraints:
 * - 1 <= haystack.length, needle.length <= 10^4
 * - haystack and needle consist of only lowercase English characters.
 */

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
  /*
   * Approach: Use built-in string find function
   * The find() function returns the position of the first occurrence,
   * or string::npos if not found.
   *
   * Time Complexity: O(n*m) worst case
   * Space Complexity: O(1)
   */
  int strStr(string haystack, string needle) {
    auto ind = haystack.find(needle);
    return ind != string::npos ? int(ind) : -1;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  string h1 = "sadbutsad", n1 = "sad";
  int result1 = solution.strStr(h1, n1);
  cout << "Test 1: " << result1 << " (Expected: 0)" << endl;

  // Test Case 2
  string h2 = "leetcode", n2 = "leeto";
  int result2 = solution.strStr(h2, n2);
  cout << "Test 2: " << result2 << " (Expected: -1)" << endl;

  return 0;
}
