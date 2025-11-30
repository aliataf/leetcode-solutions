/*
 * Problem: 100. Same Tree
 * Link: https://leetcode.com/problems/same-tree/
 * Difficulty: Easy
 *
 * Description:
 * Given the roots of two binary trees p and q, write a function to check if they
 * are the same or not. Two binary trees are considered the same if they are
 * structurally identical, and the nodes have the same value.
 *
 * Example 1:
 * Input: p = [1,2,3], q = [1,2,3]
 * Output: true
 *
 * Example 2:
 * Input: p = [1,2], q = [1,null,2]
 * Output: false
 *
 * Example 3:
 * Input: p = [1,2,1], q = [1,1,2]
 * Output: false
 *
 * Constraints:
 * - The number of nodes in both trees is in the range [0, 100].
 * - -10^4 <= Node.val <= 10^4
 */

#include <iostream>

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
     * Approach: Recursive DFS
     * Compare two trees recursively by checking:
     * 1. If both nodes are null, they are the same
     * 2. If one is null and the other isn't, they are different
     * 3. If values differ, they are different
     * 4. Recursively check left and right subtrees
     *
     * Time Complexity: O(min(m, n)) - where m and n are number of nodes in p and q
     * Space Complexity: O(min(m, n)) - recursion stack depth
     */
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) return true;
        if (p == nullptr || q == nullptr) return false;
        if (p->val != q->val) return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
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
    
    // Test Case 1: p = [1,2,3], q = [1,2,3]
    TreeNode* p1 = new TreeNode(1);
    p1->left = new TreeNode(2);
    p1->right = new TreeNode(3);
    TreeNode* q1 = new TreeNode(1);
    q1->left = new TreeNode(2);
    q1->right = new TreeNode(3);
    bool result1 = solution.isSameTree(p1, q1);
    cout << "Test 1: " << (result1 ? "true" : "false") << " (Expected: true)" << endl;
    deleteTree(p1);
    deleteTree(q1);
    
    // Test Case 2: p = [1,2], q = [1,null,2]
    TreeNode* p2 = new TreeNode(1);
    p2->left = new TreeNode(2);
    TreeNode* q2 = new TreeNode(1);
    q2->right = new TreeNode(2);
    bool result2 = solution.isSameTree(p2, q2);
    cout << "Test 2: " << (result2 ? "true" : "false") << " (Expected: false)" << endl;
    deleteTree(p2);
    deleteTree(q2);
    
    // Test Case 3: p = [1,2,1], q = [1,1,2]
    TreeNode* p3 = new TreeNode(1);
    p3->left = new TreeNode(2);
    p3->right = new TreeNode(1);
    TreeNode* q3 = new TreeNode(1);
    q3->left = new TreeNode(1);
    q3->right = new TreeNode(2);
    bool result3 = solution.isSameTree(p3, q3);
    cout << "Test 3: " << (result3 ? "true" : "false") << " (Expected: false)" << endl;
    deleteTree(p3);
    deleteTree(q3);
    
    // Test Case 4: p = [], q = []
    TreeNode* p4 = nullptr;
    TreeNode* q4 = nullptr;
    bool result4 = solution.isSameTree(p4, q4);
    cout << "Test 4: " << (result4 ? "true" : "false") << " (Expected: true)" << endl;
    
    // Test Case 5: p = [1], q = [1]
    TreeNode* p5 = new TreeNode(1);
    TreeNode* q5 = new TreeNode(1);
    bool result5 = solution.isSameTree(p5, q5);
    cout << "Test 5: " << (result5 ? "true" : "false") << " (Expected: true)" << endl;
    deleteTree(p5);
    deleteTree(q5);
    
    return 0;
}

