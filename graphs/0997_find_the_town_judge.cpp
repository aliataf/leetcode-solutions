/*
 * Problem: 997. Find the Town Judge
 * Link: https://leetcode.com/problems/find-the-town-judge/
 * Difficulty: Easy
 *
 * Description:
 * In a town, there are n people labeled from 1 to n. There is a rumor that
 * one of these people is secretly the town judge.
 *
 * If the town judge exists, then:
 * 1. The town judge trusts nobody.
 * 2. Everybody (except for the town judge) trusts the town judge.
 * 3. There is exactly one person that satisfies properties 1 and 2.
 *
 * You are given an array trust where trust[i] = [ai, bi] representing that
 * the person labeled ai trusts the person labeled bi. If a trust relationship
 * does not exist in trust array, then such a trust relationship does not exist.
 *
 * Return the label of the town judge if the town judge exists and can be
 * identified, or return -1 otherwise.
 *
 * Example:
 * Input: n = 2, trust = [[1,2]]
 * Output: 2
 *
 * Input: n = 3, trust = [[1,3],[2,3]]
 * Output: 3
 *
 * Input: n = 3, trust = [[1,3],[2,3],[3,1]]
 * Output: -1
 *
 * Constraints:
 * - 1 <= n <= 1000
 * - 0 <= trust.length <= 10^4
 * - trust[i].length == 2
 * - All the pairs of trust are unique.
 * - ai != bi
 * - 1 <= ai, bi <= n
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Indegree and Outdegree Count
   *
   * Key Insight: Model this as a directed graph problem where trust[i] = [a, b]
   * represents an edge from a to b. The town judge is the node with:
   * - Indegree = n - 1 (everyone trusts them)
   * - Outdegree = 0 (they trust nobody)
   *
   * Strategy:
   * 1. Build indegree and outdegree arrays for all n people
   * 2. For each trust relationship [a, b]:
   *    - a trusts someone, so outdegree[a]++
   *    - b is trusted by someone, so indegree[b]++
   * 3. Find the person with indegree = n-1 and outdegree = 0
   *
   * Time Complexity: O(T + n) where T = trust.length
   * Space Complexity: O(n) - two arrays of size n+1
   */
  int findJudge(int n, vector<vector<int>> &trust) {
    vector<int> indegree(n + 1, 0);
    vector<int> outdegree(n + 1, 0);

    for (auto trustItem : trust) {
      outdegree[trustItem[0]]++;
      indegree[trustItem[1]]++;
    }

    for (int i = 1; i <= n; i++) {
      if (indegree[i] == n - 1 && outdegree[i] == 0) {
        return i;
      }
    }

    return -1;
  }

  /*
   * Approach 2: Single Array (Net Trust Score)
   *
   * Key Insight: Instead of tracking indegree and outdegree separately,
   * use a single "trust score" where:
   * - Being trusted adds +1
   * - Trusting someone adds -1
   *
   * The judge will have a net score of exactly n - 1.
   *
   * Time Complexity: O(T + n) where T = trust.length
   * Space Complexity: O(n) - single array of size n+1
   */
  int findJudgeOptimized(int n, vector<vector<int>> &trust) {
    vector<int> trustScore(n + 1, 0);

    for (const auto &t : trust) {
      trustScore[t[0]]--; // Trusts someone, loses a point
      trustScore[t[1]]++; // Is trusted, gains a point
    }

    for (int i = 1; i <= n; i++) {
      if (trustScore[i] == n - 1) {
        return i;
      }
    }

    return -1;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  cout << "=== Approach 1: Indegree/Outdegree ===" << endl;

  // Test Case 1
  vector<vector<int>> trust1 = {{1, 2}};
  cout << "Test 1: n=2, trust=[[1,2]] -> " << solution.findJudge(2, trust1)
       << endl;
  // Expected: 2

  // Test Case 2
  vector<vector<int>> trust2 = {{1, 3}, {2, 3}};
  cout << "Test 2: n=3, trust=[[1,3],[2,3]] -> "
       << solution.findJudge(3, trust2) << endl;
  // Expected: 3

  // Test Case 3
  vector<vector<int>> trust3 = {{1, 3}, {2, 3}, {3, 1}};
  cout << "Test 3: n=3, trust=[[1,3],[2,3],[3,1]] -> "
       << solution.findJudge(3, trust3) << endl;
  // Expected: -1

  // Test Case 4: Single person (they are the judge)
  vector<vector<int>> trust4 = {};
  cout << "Test 4: n=1, trust=[] -> " << solution.findJudge(1, trust4) << endl;
  // Expected: 1

  cout << endl << "=== Approach 2: Net Trust Score ===" << endl;

  // Test Case 5
  vector<vector<int>> trust5 = {{1, 2}};
  cout << "Test 5: n=2, trust=[[1,2]] -> "
       << solution.findJudgeOptimized(2, trust5) << endl;
  // Expected: 2

  // Test Case 6
  vector<vector<int>> trust6 = {{1, 3}, {2, 3}};
  cout << "Test 6: n=3, trust=[[1,3],[2,3]] -> "
       << solution.findJudgeOptimized(3, trust6) << endl;
  // Expected: 3

  // Test Case 7: Everyone trusts everyone (no judge)
  vector<vector<int>> trust7 = {{1, 2}, {2, 1}};
  cout << "Test 7: n=2, trust=[[1,2],[2,1]] -> "
       << solution.findJudgeOptimized(2, trust7) << endl;
  // Expected: -1

  return 0;
}
