/*
 * Problem: 210. Course Schedule II
 * Link: https://leetcode.com/problems/course-schedule-ii/
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
 * Return the ordering of courses you should take to finish all courses.
 * If there are many valid answers, return any of them. If it is impossible
 * to finish all courses, return an empty array.
 *
 * Example:
 * Input: numCourses = 2, prerequisites = [[1,0]]
 * Output: [0,1]
 * Explanation: There are 2 courses to take. To take course 1 you should
 *              have finished course 0. So the correct order is [0,1].
 *
 * Input: numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
 * Output: [0,2,1,3] or [0,1,2,3]
 * Explanation: There are 4 courses to take. To take course 3 you should
 *              have finished both courses 1 and 2. Both courses 1 and 2
 *              should be taken after course 0.
 *
 * Input: numCourses = 1, prerequisites = []
 * Output: [0]
 *
 * Constraints:
 * - 1 <= numCourses <= 2000
 * - 0 <= prerequisites.length <= numCourses * (numCourses - 1)
 * - prerequisites[i].length == 2
 * - 0 <= ai, bi < numCourses
 * - ai != bi
 * - All the pairs [ai, bi] are distinct.
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
   * Key Insight: This is an extension of Course Schedule I (problem 207).
   * Instead of just detecting if completion is possible, we need to return
   * the actual order in which courses should be taken.
   *
   * Strategy (Kahn's Algorithm):
   * 1. Build adjacency list and compute indegree for each course
   * 2. Add all courses with indegree 0 to a queue (no prerequisites)
   * 3. Process courses from queue, adding each to result:
   *    - For each neighbor, decrement their indegree
   *    - If neighbor's indegree becomes 0, add to queue
   * 4. If result contains all courses, return it; otherwise return empty
   *
   * The order in which courses are dequeued gives us a valid topological order.
   *
   * Time Complexity: O(V + E) where V = numCourses, E = prerequisites.length
   * Space Complexity: O(V + E) for adjacency list, queue, and result
   */
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
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

    vector<int> taken;

    // Process courses in topological order
    while (!q.empty()) {
      int course = q.front();
      q.pop();
      taken.push_back(course);

      // "Taking" this course reduces indegree of dependent courses
      for (int next : adj[course]) {
        if (--indegree[next] == 0) {
          q.push(next);
        }
      }
    }

    // Return order if all courses can be taken, otherwise empty array
    return taken.size() == numCourses ? taken : vector<int>{};
  }
};

// ============== Test Cases ==============
void printResult(const vector<int> &result) {
  if (result.empty()) {
    cout << "[]" << endl;
    return;
  }
  cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    cout << result[i];
    if (i < result.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1: Simple dependency
  vector<vector<int>> prereqs1 = {{1, 0}};
  cout << "Test 1: numCourses=2, [[1,0]] -> ";
  printResult(solution.findOrder(2, prereqs1));
  // Expected: [0,1]

  // Test Case 2: Multiple valid orders
  vector<vector<int>> prereqs2 = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
  cout << "Test 2: numCourses=4, [[1,0],[2,0],[3,1],[3,2]] -> ";
  printResult(solution.findOrder(4, prereqs2));
  // Expected: [0,1,2,3] or [0,2,1,3]

  // Test Case 3: Single course
  vector<vector<int>> prereqs3 = {};
  cout << "Test 3: numCourses=1, [] -> ";
  printResult(solution.findOrder(1, prereqs3));
  // Expected: [0]

  // Test Case 4: Cycle exists - impossible
  vector<vector<int>> prereqs4 = {{1, 0}, {0, 1}};
  cout << "Test 4: numCourses=2, [[1,0],[0,1]] -> ";
  printResult(solution.findOrder(2, prereqs4));
  // Expected: [] (cycle)

  // Test Case 5: No prerequisites
  vector<vector<int>> prereqs5 = {};
  cout << "Test 5: numCourses=3, [] -> ";
  printResult(solution.findOrder(3, prereqs5));
  // Expected: [0,1,2] or any permutation

  // Test Case 6: Linear chain
  vector<vector<int>> prereqs6 = {{1, 0}, {2, 1}, {3, 2}};
  cout << "Test 6: numCourses=4, [[1,0],[2,1],[3,2]] -> ";
  printResult(solution.findOrder(4, prereqs6));
  // Expected: [0,1,2,3]

  return 0;
}
