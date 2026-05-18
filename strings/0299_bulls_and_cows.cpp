/*
 * Problem: 299. Bulls and Cows
 * Link: https://leetcode.com/problems/bulls-and-cows/
 * Difficulty: Medium
 *
 * Description:
 * You are playing the Bulls and Cows game with your friend. You write down a
 * secret number and ask your friend to guess what the number is. When your
 * friend makes a guess, you provide a hint:
 *   - The number of "bulls": digits in the guess that are in the correct
 *     position.
 *   - The number of "cows": digits in the guess that exist in the secret but
 *     are in the wrong position. Specifically, non-bull digits of the guess
 *     that could be rearranged to become bulls.
 * Return the hint formatted as "xAyB", where x is the number of bulls and y
 * is the number of cows. Both strings may contain duplicate digits.
 *
 * Example 1:
 * Input: secret = "1807", guess = "7810"
 * Output: "1A3B"
 *
 * Example 2:
 * Input: secret = "1123", guess = "0111"
 * Output: "1A1B"
 * Explanation: Only one of the two unmatched 1s in the guess counts as a cow,
 * because there is only one non-bull 1 left in the secret to pair with.
 *
 * Constraints:
 * - 1 <= secret.length, guess.length <= 1000
 * - secret.length == guess.length
 * - secret and guess consist of digits only.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Two-Pass Counting Over Non-Bull Digits
   *
   * Key Insight: A cow is a guess digit that has a *non-bull* match left over
   * in the secret. If we count digit frequencies of the secret only at
   * positions where it disagrees with the guess, then walking the guess a
   * second time and consuming from that counter is exactly the right thing —
   * bulls never enter the counter, so they can't be double-counted as cows.
   *
   * Strategy:
   * 1. Pass 1: for each index where secret[i] != guess[i], increment
   *    count[secret[i]]. This builds a frequency map of the digits in the
   *    secret that are still "available" to be matched as cows.
   * 2. Pass 2: walk both strings together.
   *      - If secret[i] == guess[i], it's a bull (a++).
   *      - Otherwise, if count[guess[i]] > 0, it's a cow: decrement
   *        count[guess[i]] and b++.
   * 3. Format the result as "<a>A<b>B".
   *
   * Time Complexity: O(n) - two linear passes over strings of length n.
   * Space Complexity: O(1) - the frequency array has a fixed size of 10.
   */
  string getHint(string secret, string guess) {
    int a = 0, b = 0;
    vector<int> count = vector<int>(10, 0);

    for (int i = 0; i < secret.size(); i++)
      if (secret[i] != guess[i]) count[secret[i] - '0']++;

    for (int i = 0; i < secret.size(); i++) {
      int s = secret[i] - '0';
      int g = guess[i] - '0';
      if (s == g) a++;
      else if (count[g] > 0) {
        count[g]--;
        b++;
      }
    }

    return to_string(a) + 'A' + to_string(b) + 'B';
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1
  cout << "Test 1: " << solution.getHint("1807", "7810") << endl;
  // Expected: 1A3B

  // Test Case 2: duplicates in secret and guess
  cout << "Test 2: " << solution.getHint("1123", "0111") << endl;
  // Expected: 1A1B

  // Test Case 3: all bulls
  cout << "Test 3: " << solution.getHint("1234", "1234") << endl;
  // Expected: 4A0B

  // Test Case 4: all cows
  cout << "Test 4: " << solution.getHint("1234", "4321") << endl;
  // Expected: 0A4B

  // Test Case 5: no matches at all
  cout << "Test 5: " << solution.getHint("1234", "5678") << endl;
  // Expected: 0A0B

  // Test Case 6: single digit
  cout << "Test 6: " << solution.getHint("1", "0") << endl;
  // Expected: 0A0B

  return 0;
}
