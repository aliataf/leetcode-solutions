/*
 * Problem: 94. Binary Tree Inorder Traversal
 * Link: https://leetcode.com/problems/binary-tree-inorder-traversal/
 * Difficulty: Easy
 *
 * Description:
 * Given the root of a binary tree, return the inorder traversal of its nodes'
 * values.
 *
 * Example 1:
 * Input: root = [1,null,2,3]
 * Output: [1,3,2]
 *
 * Example 2:
 * Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]
 * Output: [4,2,6,5,7,1,3,9,8]
 *
 * Example 3:
 * Input: root = []
 * Output: []
 *
 * Example 4:
 * Input: root = [1]
 * Output: [1]
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 100].
 * - -100 <= Node.val <= 100
 */

#include <iostream>
#include <stack>
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
   * Approach: Iterative Inorder Traversal using Stack
   * Use a stack to simulate the recursive call stack. Process nodes in
   * left-root-right order by:
   * 1. Push all left nodes onto the stack
   * 2. Pop and process the current node
   * 3. Move to the right subtree
   *
   * Time Complexity: O(n) - visit each node exactly once
   * Space Complexity: O(h) - where h is the height of the tree (stack space)
   */
  vector<int> inorderTraversal(TreeNode *root) {
    vector<int> res;
    stack<TreeNode *> st;
    TreeNode *curr = root;

    while (curr != nullptr || !st.empty()) {
      while (curr != nullptr) {
        st.push(curr);
        curr = curr->left;
      }

      curr = st.top();
      st.pop();
      res.push_back(curr->val);

      curr = curr->right;
    }

    return res;
  }
};

// ============== Helper Functions ==============
void printVector(const vector<int> &vec) {
  cout << "[";
  for (size_t i = 0; i < vec.size(); i++) {
    cout << vec[i];
    if (i < vec.size() - 1) cout << ",";
  }
  cout << "]" << endl;
}

void deleteTree(TreeNode *root) {
  if (root == nullptr) return;
  deleteTree(root->left);
  deleteTree(root->right);
  delete root;
}

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1: root = [1,null,2,3]
  TreeNode *root1 = new TreeNode(1);
  root1->right = new TreeNode(2);
  root1->right->left = new TreeNode(3);
  vector<int> result1 = solution.inorderTraversal(root1);
  cout << "Test 1: ";
  printVector(result1); // Expected: [1,3,2]
  deleteTree(root1);

  // Test Case 2: root = [1,2,3,4,5,null,8,null,null,6,7,9]
  // Tree structure:
  //        1
  //       / \
    //      2   3
  //     / \   \
    //    4   5   8
  //       / \   \
    //      6   7   9
  TreeNode *root2 = new TreeNode(1);
  root2->left = new TreeNode(2);
  root2->right = new TreeNode(3);
  root2->left->left = new TreeNode(4);
  root2->left->right = new TreeNode(5);
  root2->right->right = new TreeNode(8);
  root2->left->right->left = new TreeNode(6);
  root2->left->right->right = new TreeNode(7);
  root2->right->right->right = new TreeNode(9);
  vector<int> result2 = solution.inorderTraversal(root2);
  cout << "Test 2: ";
  printVector(result2); // Expected: [4,2,6,5,7,1,3,9,8]
  deleteTree(root2);

  // Test Case 3: root = []
  TreeNode *root3 = nullptr;
  vector<int> result3 = solution.inorderTraversal(root3);
  cout << "Test 3: ";
  printVector(result3); // Expected: []

  // Test Case 4: root = [1]
  TreeNode *root4 = new TreeNode(1);
  vector<int> result4 = solution.inorderTraversal(root4);
  cout << "Test 4: ";
  printVector(result4); // Expected: [1]
  deleteTree(root4);

  return 0;
}
