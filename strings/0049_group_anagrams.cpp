/*
 * Problem: 49. Group Anagrams
 * Link: https://leetcode.com/problems/group-anagrams/
 * Difficulty: Medium
 *
 * Description:
 * Given an array of strings strs, group the anagrams together. You can return
 * the answer in any order. An Anagram is a word or phrase formed by rearranging
 * the letters of a different word or phrase, typically using all the original
 * letters exactly once.
 *
 * Example:
 * Input: strs = ["eat","tea","tan","ate","nat","bat"]
 * Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
 *
 * Input: strs = [""]
 * Output: [[""]]
 *
 * Input: strs = ["a"]
 * Output: [["a"]]
 *
 * Constraints:
 * - 1 <= strs.length <= 10^4
 * - 0 <= strs[i].length <= 100
 * - strs[i] consists of lowercase English letters.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Hash Map with Sorted String as Key
   *
   * Key Insight: Anagrams will produce the same string when sorted.
   * For example, "eat", "tea", "ate" all become "aet" when sorted.
   *
   * Strategy:
   * 1. Create a hash map where the key is the sorted version of each string
   * 2. For each string in the input:
   *    - Sort the string to create a key
   *    - Add the original string to the vector associated with that key
   * 3. Extract all values from the hash map to get grouped anagrams
   *
   * Time Complexity: O(n * k log k) where n is the number of strings and k is
   * the max length
   * Space Complexity: O(n * k) to store all strings in the hash map
   */
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    unordered_map<string, vector<string>> mp;
    for (auto it = strs.begin(); it != strs.end(); it++) {
      string s = *it;
      sort(s.begin(), s.end());
      mp[s].push_back(*it);
    }
    vector<vector<string>> v;
    for (auto it = mp.begin(); it != mp.end(); it++) {
      v.push_back((*it).second);
    }

    return v;
  }
};

// ============== Test Cases ==============
void printResult(const vector<vector<string>> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    cout << "[";
    for (size_t j = 0; j < result[i].size(); ++j) {
      cout << "\"" << result[i][j] << "\"";
      if (j < result[i].size() - 1)
        cout << ",";
    }
    cout << "]";
    if (i < result.size() - 1)
      cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  vector<string> strs1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
  vector<vector<string>> result1 = solution.groupAnagrams(strs1);
  cout << "Test 1: ";
  printResult(result1);
  // Expected: [["bat"],["nat","tan"],["ate","eat","tea"]] (order may vary)

  // Test Case 2
  vector<string> strs2 = {""};
  vector<vector<string>> result2 = solution.groupAnagrams(strs2);
  cout << "Test 2: ";
  printResult(result2);
  // Expected: [[""]]

  // Test Case 3
  vector<string> strs3 = {"a"};
  vector<vector<string>> result3 = solution.groupAnagrams(strs3);
  cout << "Test 3: ";
  printResult(result3);
  // Expected: [["a"]]

  return 0;
}
