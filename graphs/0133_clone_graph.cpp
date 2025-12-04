/*
 * Problem: 133. Clone Graph
 * Link: https://leetcode.com/problems/clone-graph/
 * Difficulty: Medium
 *
 * Description:
 * Given a reference of a node in a connected undirected graph, return a deep
 * copy (clone) of the graph. Each node in the graph contains a value (int) and
 * a list of its neighbors.
 *
 * Example:
 * Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
 * Output: [[2,4],[1,3],[2,4],[1,3]]
 *
 * Constraints:
 * - The number of nodes in the graph is in the range [0, 100].
 * - 1 <= Node.val <= 100
 * - Node.val is unique for each node.
 * - There are no repeated edges and no self-loops in the graph.
 * - The Graph is connected and all nodes can be visited starting from the given
 * node.
 */

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Definition for a Node.
class Node {
public:
  int val;
  vector<Node *> neighbors;
  Node() {
    val = 0;
    neighbors = vector<Node *>();
  }
  Node(int _val) {
    val = _val;
    neighbors = vector<Node *>();
  }
  Node(int _val, vector<Node *> _neighbors) {
    val = _val;
    neighbors = _neighbors;
  }
};

class Solution {
public:
  /*
   * Approach: DFS with Hash Map
   *
   * Strategy:
   * 1. Use a hash map to track original node -> cloned node mapping.
   * 2. For each node, create a clone and add it to the map.
   * 3. Recursively clone all neighbors.
   * 4. If a neighbor is already cloned (in map), use the existing clone.
   *
   * Time Complexity: O(V + E) - visit each node and edge once
   * Space Complexity: O(V) - for the hash map and recursion stack
   */
  Node *cloneGraph(Node *node) {
    if (node == nullptr) return nullptr;
    unordered_map<Node *, Node *> m;
    return cloneGraph(node, m);
  }

  Node *cloneGraph(Node *node, unordered_map<Node *, Node *> &m) {
    Node *clone = new Node(node->val);
    m[node] = clone;
    for (auto neighbor : node->neighbors) {
      if (m[neighbor]) clone->neighbors.push_back(m[neighbor]);
      else clone->neighbors.push_back(cloneGraph(neighbor, m));
    }
    return clone;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1: Simple graph with 4 nodes
  Node *node1 = new Node(1);
  Node *node2 = new Node(2);
  Node *node3 = new Node(3);
  Node *node4 = new Node(4);
  node1->neighbors = {node2, node4};
  node2->neighbors = {node1, node3};
  node3->neighbors = {node2, node4};
  node4->neighbors = {node1, node3};

  Node *clone = solution.cloneGraph(node1);
  cout << "Test 1: Clone value = " << clone->val << " (Expected: 1)" << endl;
  cout << "Test 1: Different ptr = " << (clone != node1 ? "true" : "false")
       << " (Expected: true)" << endl;

  // Test Case 2: Empty graph
  Node *empty = solution.cloneGraph(nullptr);
  cout << "Test 2: " << (empty == nullptr ? "nullptr" : "not null")
       << " (Expected: nullptr)" << endl;

  return 0;
}
