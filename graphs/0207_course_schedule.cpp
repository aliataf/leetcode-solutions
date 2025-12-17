/*
 * Problem: 207. Course Schedule
 * Link: https://leetcode.com/problems/course-schedule/
 * Difficulty: Medium
 *
 * Description:
 * There are a total of numCourses courses you have to take, labeled from
 * 0 to numCourses - 1. You are given an array prerequisites where
 * prerequisites[i] = [ai, bi] indicates that you must take course bi first
 * if you want to take course ai.
 *
 * For example, the pair [0, 1], indicates that to take course 0 you have
 * to first take course 1.
 *
 * Return true if you can finish all courses. Otherwise, return false.
 *
 * Example:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: true
 * Explanation: There are 2 courses to take. To take course 1 you should
 *              have finished course 0. So it is possible.
 *
 * Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
 * Output: false
 * Explanation: There are 2 courses to take. To take course 1 you should
 *              have finished course 0, and to take course 0 you should also
 *              have finished course 1. So it is impossible.
 *
 * Constraints:
 * - 1 <= numCourses <= 2000
 * - 0 <= prerequisites.length <= 5000
 * - prerequisites[i].length == 2
 * - 0 <= ai, bi < numCourses
 * - All the pairs prerequisites[i] are unique.
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  /*
   * Approach: Topological Sort using Kahn's Algorithm (BFS)
   *
   * Key Insight: This problem is equivalent to detecting if a directed graph
   * has a cycle. If we can perform a valid topological sort (process all
   * nodes), then there's no cycle and all courses can be completed.
   *
   * Strategy (Kahn's Algorithm):
   * 1. Build adjacency list and compute indegree for each course
   * 2. Add all courses with indegree 0 to a queue (no prerequisites)
   * 3. Process courses from queue:
   *    - For each neighbor, decrement their indegree
   *    - If neighbor's indegree becomes 0, add to queue
   * 4. If we processed all courses, return true; otherwise there's a cycle
   *
   * Why it works:
   * - Courses with indegree 0 have no unmet prerequisites
   * - Processing a course "unlocks" dependent courses
   * - If a cycle exists, nodes in the cycle never reach indegree 0
   *
   * Time Complexity: O(V + E) where V = numCourses, E = prerequisites.length
   * Space Complexity: O(V + E) for adjacency list and queue
   */
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);

    // Build adjacency list: edge from prerequisite to dependent course
    for (auto &p : prerequisites) {
      adj[p[1]].push_back(p[0]);
      indegree[p[0]]++;
    }

    // Initialize queue with courses having no prerequisites
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
      if (indegree[i] == 0) {
        q.push(i);
      }
    }

    int taken = 0;

    // Process courses in topological order
    while (!q.empty()) {
      int course = q.front();
      q.pop();
      taken++;

      // "Taking" this course reduces indegree of dependent courses
      for (int next : adj[course]) {
        if (--indegree[next] == 0) {
          q.push(next);
        }
      }
    }

    // If we took all courses, no cycle exists
    return taken == numCourses;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1: Simple dependency chain
  vector<vector<int>> prereqs1 = {{1, 0}};
  cout << "Test 1: numCourses=2, [[1,0]] -> "
       << (solution.canFinish(2, prereqs1) ? "true" : "false") << endl;
  // Expected: true (take 0 first, then 1)

  // Test Case 2: Cycle exists
  vector<vector<int>> prereqs2 = {{1, 0}, {0, 1}};
  cout << "Test 2: numCourses=2, [[1,0],[0,1]] -> "
       << (solution.canFinish(2, prereqs2) ? "true" : "false") << endl;
  // Expected: false (0 needs 1, 1 needs 0 - impossible)

  // Test Case 3: No prerequisites
  vector<vector<int>> prereqs3 = {};
  cout << "Test 3: numCourses=3, [] -> "
       << (solution.canFinish(3, prereqs3) ? "true" : "false") << endl;
  // Expected: true (all courses are independent)

  // Test Case 4: Multiple dependencies, no cycle
  vector<vector<int>> prereqs4 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
  cout << "Test 4: numCourses=4, [[1,0],[2,0],[3,1],[3,2]] -> "
       << (solution.canFinish(4, prereqs4) ? "true" : "false") << endl;
  // Expected: true (0 -> 1,2 -> 3)

  // Test Case 5: Longer cycle
  vector<vector<int>> prereqs5 = {{1, 0}, {2, 1}, {0, 2}};
  cout << "Test 5: numCourses=3, [[1,0],[2,1],[0,2]] -> "
       << (solution.canFinish(3, prereqs5) ? "true" : "false") << endl;
  // Expected: false (cycle: 0 -> 1 -> 2 -> 0)

  // Test Case 6: Single course
  vector<vector<int>> prereqs6 = {};
  cout << "Test 6: numCourses=1, [] -> "
       << (solution.canFinish(1, prereqs6) ? "true" : "false") << endl;
  // Expected: true

  return 0;
}
