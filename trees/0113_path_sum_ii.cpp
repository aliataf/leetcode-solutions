/*
 * Problem: 113. Path Sum II
 * Link: https://leetcode.com/problems/path-sum-ii/
 * Difficulty: Medium
 *
 * Description:
 * Given the root of a binary tree and an integer targetSum, return all
 * root-to-leaf paths where the sum of the node values in the path equals
 * targetSum. Each path should be returned as a list of the node values, not
 * node references. A root-to-leaf path is a path starting from the root and
 * ending at any leaf node. A leaf is a node with no children.
 *
 * Example 1:
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
 * Output: [[5,4,11,2],[5,8,4,5]]
 * Explanation: There are two paths whose sum equals targetSum:
 * 5 + 4 + 11 + 2 = 22
 * 5 + 8 + 4 + 5 = 22
 *
 * Example 2:
 * Input: root = [1,2,3], targetSum = 5
 * Output: []
 *
 * Example 3:
 * Input: root = [1,2], targetSum = 0
 * Output: []
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 5000].
 * - -1000 <= Node.val <= 1000
 * - -1000 <= targetSum <= 1000
 */

#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  /*
   * Approach: Iterative DFS using Stack
   * Use a stack to store pairs of (node, path). For each node, track the path
   * from root to that node. When we reach a leaf node, check if the path sum
   * equals targetSum. If so, add the path to the result.
   *
   * Time Complexity: O(n * h) - visit each node and for each leaf, sum the path
   * Space Complexity: O(h^2) - stack stores paths of length up to h
   */
  vector<vector<int>> pathSum(TreeNode *root, int targetSum) {
    if (root == nullptr) return {};

    vector<vector<int>> res;
    stack<pair<TreeNode *, vector<int>>> s;
    s.push({root, {root->val}});

    while (!s.empty()) {
      pair<TreeNode *, vector<int>> top = s.top();
      s.pop();
      TreeNode *node = top.first;
      vector<int> currentPath = top.second;
      int currentSum = sumVector(currentPath);

      if (node->left == nullptr && node->right == nullptr &&
          currentSum == targetSum) {
        res.push_back(currentPath);
      }

      if (node->right != nullptr) {
        currentPath.push_back(node->right->val);
        s.push({node->right, currentPath});
        currentPath.pop_back();
      }

      if (node->left != nullptr) {
        currentPath.push_back(node->left->val);
        s.push({node->left, currentPath});
        currentPath.pop_back();
      }
    }

    return res;
  }

private:
  int sumVector(vector<int> v) {
    int sum = 0;
    for (auto c : v) {
      sum += c;
    }
    return sum;
  }
};

// ============== Helper Functions ==============
void deleteTree(TreeNode *root) {
  if (root == nullptr) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

void printVector(const vector<int> &vec) {
  cout << "[";
  for (size_t i = 0; i < vec.size(); i++) {
    cout << vec[i];
    if (i < vec.size() - 1) cout << ",";
  }
  cout << "]";
}

void printResult(const vector<vector<int>> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    cout << "[";
    for (size_t j = 0; j < result[i].size(); j++) {
      cout << result[i][j];
      if (j < result[i].size() - 1) cout << ",";
    }
    cout << "]";
    if (i < result.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
  // Tree structure:
  //         5
  //       /   \
    //      4     8
  //     /     / \
    //    11    13  4
  //   /  \      / \
    //  7    2     5  1
  TreeNode *root1 = new TreeNode(5);
  root1->left = new TreeNode(4);
  root1->right = new TreeNode(8);
  root1->left->left = new TreeNode(11);
  root1->left->left->left = new TreeNode(7);
  root1->left->left->right = new TreeNode(2);
  root1->right->left = new TreeNode(13);
  root1->right->right = new TreeNode(4);
  root1->right->right->left = new TreeNode(5);
  root1->right->right->right = new TreeNode(1);
  vector<vector<int>> result1 = solution.pathSum(root1, 22);
  cout << "Test 1: ";
  printResult(result1); // Expected: [[5,4,11,2],[5,8,4,5]]
  deleteTree(root1);

  // Test Case 2: root = [1,2,3], targetSum = 5
  TreeNode *root2 = new TreeNode(1);
  root2->left = new TreeNode(2);
  root2->right = new TreeNode(3);
  vector<vector<int>> result2 = solution.pathSum(root2, 5);
  cout << "Test 2: ";
  printResult(result2); // Expected: []
  deleteTree(root2);

  // Test Case 3: root = [1,2], targetSum = 0
  TreeNode *root3 = new TreeNode(1);
  root3->left = new TreeNode(2);
  vector<vector<int>> result3 = solution.pathSum(root3, 0);
  cout << "Test 3: ";
  printResult(result3); // Expected: []
  deleteTree(root3);

  // Test Case 4: root = [1,2], targetSum = 3
  TreeNode *root4 = new TreeNode(1);
  root4->left = new TreeNode(2);
  vector<vector<int>> result4 = solution.pathSum(root4, 3);
  cout << "Test 4: ";
  printResult(result4); // Expected: [[1,2]]
  deleteTree(root4);

  // Test Case 5: root = [1], targetSum = 1
  TreeNode *root5 = new TreeNode(1);
  vector<vector<int>> result5 = solution.pathSum(root5, 1);
  cout << "Test 5: ";
  printResult(result5); // Expected: [[1]]
  deleteTree(root5);

  return 0;
}
