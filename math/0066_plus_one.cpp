/*
 * Problem: 66. Plus One
 * Link: https://leetcode.com/problems/plus-one/
 * Difficulty: Easy
 *
 * Description:
 * You are given a large integer represented as an integer array digits, where
 * each digits[i] is the ith digit of the integer. The digits are ordered from
 * most significant to least significant in left-to-right order. The large
 * integer does not contain any leading 0's. Increment the large integer by one
 * and return the resulting array of digits.
 *
 * Example:
 * Input: digits = [1,2,3]
 * Output: [1,2,4]
 * Explanation: The array represents the integer 123. Incrementing by one gives
 * 123 + 1 = 124.
 *
 * Input: digits = [4,3,2,1]
 * Output: [4,3,2,2]
 *
 * Input: digits = [9]
 * Output: [1,0]
 *
 * Constraints:
 * - 1 <= digits.length <= 100
 * - 0 <= digits[i] <= 9
 * - digits does not contain any leading 0's.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Simulate addition with carry
   *
   * Strategy:
   * 1. Start from the last digit and add 1
   * 2. Iterate from right to left, handling carries
   * 3. If a digit becomes 10, set it to 0 and carry 1 to the next position
   * 4. If we reach the beginning and still have a carry, insert 1 at the front
   *
   * Time Complexity: O(n) where n is the number of digits
   * Space Complexity: O(1) if we don't count the output, O(n) in worst case
   */
  vector<int> plusOne(vector<int> &digits) {
    int n = digits.size() - 1;
    digits[n]++;
    while (n >= 0) {
      if (digits[n] == 10) {
        digits[n] = 0;
        if (n > 0) {
          digits[n - 1]++;
        } else {
          digits.insert(digits.begin(), 1);
        }
      }
      n--;
    }

    return digits;
  }
};

// ============== Test Cases ==============
void printResult(const vector<int> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i < result.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  vector<int> digits1 = {1, 2, 3};
  vector<int> result1 = solution.plusOne(digits1);
  cout << "Test 1: ";
  printResult(result1);
  // Expected: [1,2,4]

  // Test Case 2
  vector<int> digits2 = {4, 3, 2, 1};
  vector<int> result2 = solution.plusOne(digits2);
  cout << "Test 2: ";
  printResult(result2);
  // Expected: [4,3,2,2]

  // Test Case 3
  vector<int> digits3 = {9};
  vector<int> result3 = solution.plusOne(digits3);
  cout << "Test 3: ";
  printResult(result3);
  // Expected: [1,0]

  // Test Case 4
  vector<int> digits4 = {9, 9, 9};
  vector<int> result4 = solution.plusOne(digits4);
  cout << "Test 4: ";
  printResult(result4);
  // Expected: [1,0,0,0]

  return 0;
}
