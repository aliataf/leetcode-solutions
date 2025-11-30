/*
 * Problem: 112. Path Sum
 * Link: https://leetcode.com/problems/path-sum/
 * Difficulty: Easy
 *
 * Description:
 * Given the root of a binary tree and an integer targetSum, return true if the
 * tree has a root-to-leaf path such that adding up all the values along the path
 * equals targetSum. A leaf is a node with no children.
 *
 * Example 1:
 * Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
 * Output: true
 * Explanation: The path with the target sum is shown.
 *
 * Example 2:
 * Input: root = [1,2,3], targetSum = 5
 * Output: false
 * Explanation: There are two root-to-leaf paths in the tree:
 * (1 -> 2): The sum is 3.
 * (1 -> 3): The sum is 5.
 * There is no root-to-leaf path with sum = 5.
 *
 * Example 3:
 * Input: root = [], targetSum = 0
 * Output: false
 * Explanation: Since the tree is empty, there are no root-to-leaf paths.
 *
 * Constraints:
 * - The number of nodes in the tree is in the range [0, 5000].
 * - -1000 <= Node.val <= 1000
 * - -1000 <= targetSum <= 1000
 */

#include <iostream>
#include <stack>
#include <utility>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /*
     * Approach: Iterative DFS using Stack
     * Use a stack to store pairs of (node, currentSum). For each node, track
     * the sum from root to that node. When we reach a leaf node, check if the
     * currentSum equals targetSum.
     *
     * Time Complexity: O(n) - visit each node at most once
     * Space Complexity: O(h) - where h is the height of the tree (stack space)
     */
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return false;
        
        stack<pair<TreeNode*, int>> s;
        s.push({root, root->val});
        
        while (!s.empty()) {
            pair<TreeNode*, int> top = s.top();
            s.pop();
            TreeNode* node = top.first;
            int currentSum = top.second;
            
            if (node->left == nullptr && node->right == nullptr && currentSum == targetSum) {
                return true;
            }
            
            if (node->right != nullptr) s.push({node->right, currentSum + node->right->val});
            if (node->left != nullptr) s.push({node->left, currentSum + node->left->val});
        }
        
        return false;
    }
};

// ============== Helper Functions ==============
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ============== Test Cases ==============
int main() {
    Solution solution;
    
    // Test Case 1: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
    // Tree structure:
    //         5
    //       /   \
    //      4     8
    //     /     / \
    //    11    13  4
    //   /  \        \
    //  7    2        1
    TreeNode* root1 = new TreeNode(5);
    root1->left = new TreeNode(4);
    root1->right = new TreeNode(8);
    root1->left->left = new TreeNode(11);
    root1->left->left->left = new TreeNode(7);
    root1->left->left->right = new TreeNode(2);
    root1->right->left = new TreeNode(13);
    root1->right->right = new TreeNode(4);
    root1->right->right->right = new TreeNode(1);
    bool result1 = solution.hasPathSum(root1, 22);
    cout << "Test 1: " << (result1 ? "true" : "false") << " (Expected: true)" << endl;
    deleteTree(root1);
    
    // Test Case 2: root = [1,2,3], targetSum = 5
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    bool result2 = solution.hasPathSum(root2, 5);
    cout << "Test 2: " << (result2 ? "true" : "false") << " (Expected: false)" << endl;
    deleteTree(root2);
    
    // Test Case 3: root = [], targetSum = 0
    TreeNode* root3 = nullptr;
    bool result3 = solution.hasPathSum(root3, 0);
    cout << "Test 3: " << (result3 ? "true" : "false") << " (Expected: false)" << endl;
    
    // Test Case 4: root = [1,2], targetSum = 1
    TreeNode* root4 = new TreeNode(1);
    root4->left = new TreeNode(2);
    bool result4 = solution.hasPathSum(root4, 1);
    cout << "Test 4: " << (result4 ? "true" : "false") << " (Expected: false)" << endl;
    deleteTree(root4);
    
    // Test Case 5: root = [1,2], targetSum = 3
    TreeNode* root5 = new TreeNode(1);
    root5->left = new TreeNode(2);
    bool result5 = solution.hasPathSum(root5, 3);
    cout << "Test 5: " << (result5 ? "true" : "false") << " (Expected: true)" << endl;
    deleteTree(root5);
    
    return 0;
}

