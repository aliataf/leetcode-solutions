/*
 * Problem: 17. Letter Combinations of a Phone Number
 * Link: https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 * Difficulty: Medium
 *
 * Description:
 * Given a string containing digits from 2-9 inclusive, return all possible
 * letter combinations that the number could represent. Return the answer in any
 * order.
 *
 * Example:
 * Input: digits = "23"
 * Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]
 *
 * Input: digits = ""
 * Output: []
 *
 * Input: digits = "2"
 * Output: ["a","b","c"]
 *
 * Constraints:
 * - 0 <= digits.length <= 4
 * - digits[i] is a digit in the range ['2', '9'].
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Iterative (BFS)
   * Start with an empty string in the result. For each digit, expand every
   * existing string in the result by appending all possible letters
   * corresponding to that digit.
   *
   * Time Complexity: O(4^n * n) where n is the length of digits.
   * Space Complexity: O(4^n * n) to store the result.
   */
  vector<string> letterCombinations(string digits) {
    vector<string> mapping = {"",    "",    "abc",  "def", "ghi",
                              "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> result = {""};
    for (char digit : digits) {
      string letters = mapping[digit - '0'];
      vector<string> newCombinations;
      for (const string &prefix : result) {
        for (char letter : letters) {
          newCombinations.push_back(prefix + letter);
        }
      }
      result = newCombinations;
    }

    return result;
  }
};

// ============== Test Cases ==============
void printResult(const vector<string> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    cout << "\"" << result[i] << "\"" << (i < result.size() - 1 ? "," : "");
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  string digits1 = "23";
  vector<string> result1 = solution.letterCombinations(digits1);
  cout << "Test 1 (23): ";
  printResult(result1);
  // Expected: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

  // Test Case 2
  string digits2 = "";
  vector<string> result2 = solution.letterCombinations(digits2);
  cout << "Test 2 (\"\"): ";
  printResult(result2);
  // Expected: []

  // Test Case 3
  string digits3 = "2";
  vector<string> result3 = solution.letterCombinations(digits3);
  cout << "Test 3 (2): ";
  printResult(result3);
  // Expected: ["a","b","c"]

  return 0;
}
