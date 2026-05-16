/*
 * Problem: 24. Swap Nodes in Pairs
 * Link: https://leetcode.com/problems/swap-nodes-in-pairs/
 * Difficulty: Medium
 *
 * Description:
 * Given a linked list, swap every two adjacent nodes and return its head. You
 * must solve the problem without modifying the values in the list's nodes
 * (i.e., only nodes themselves may be changed).
 *
 * Example 1:
 * Input: head = [1,2,3,4]
 * Output: [2,1,4,3]
 *
 * Example 2:
 * Input: head = []
 * Output: []
 *
 * Example 3:
 * Input: head = [1]
 * Output: [1]
 *
 * Example 4:
 * Input: head = [1,2,3]
 * Output: [2,1,3]
 *
 * Constraints:
 * - The number of nodes in the list is in the range [0, 100].
 * - 0 <= Node.val <= 100
 */

#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  /*
   * Approach: Iterative Pointer Swapping
   *
   * Key Insight: We can swap each pair in place by rewiring three pointers per
   * pair: the previous pair's tail, the current pair's two nodes, and the next
   * pair's head. The new head is simply the second node of the first pair.
   *
   * Strategy:
   * 1. Handle base cases: empty list or single node.
   * 2. Save the new head (head->next) since it becomes the final return value.
   * 3. Track `prev` (tail of the previously swapped pair), `left` and `right`
   *    (the current pair).
   * 4. For each pair, save `temp = right->next`, then point right->left and
   *    left->temp. Connect prev->right so the prior pair links into the swap.
   * 5. Advance: prev = left, left = temp, right = temp->next. Stop when fewer
   *    than two nodes remain.
   *
   * Time Complexity: O(n) - each node is visited once.
   * Space Complexity: O(1) - only a constant number of pointers are used.
   */
  ListNode *swapPairs(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode *newHead = head->next;
    ListNode *prev = nullptr;
    ListNode *left = head;
    ListNode *right = head->next;

    while (true) {
      ListNode *temp = right->next;

      right->next = left;
      left->next = temp;

      if (prev != nullptr) prev->next = right;
      if (temp == nullptr || temp->next == nullptr) return newHead;

      prev = left;
      left = temp;
      right = temp->next;
    }

    return newHead;
  }
};

// ============== Test Cases ==============
void printList(ListNode *head) {
  cout << "[";
  while (head) {
    cout << head->val;
    if (head->next) cout << ",";
    head = head->next;
  }
  cout << "]" << endl;
}

ListNode *createList(vector<int> vals) {
  if (vals.empty()) return nullptr;
  ListNode *head = new ListNode(vals[0]);
  ListNode *curr = head;
  for (size_t i = 1; i < vals.size(); ++i) {
    curr->next = new ListNode(vals[i]);
    curr = curr->next;
  }
  return head;
}

void runTest(vector<int> vals, vector<int> expectedVals) {
  Solution solution;
  ListNode *head = createList(vals);
  cout << "Input: head = ";
  printList(head);

  ListNode *result = solution.swapPairs(head);
  cout << "Output: ";
  printList(result);

  cout << "Expected: ";
  ListNode *expected = createList(expectedVals);
  printList(expected);
  cout << endl;
}

int main() {
  runTest({1, 2, 3, 4}, {2, 1, 4, 3});
  runTest({}, {});
  runTest({1}, {1});
  runTest({1, 2, 3}, {2, 1, 3});
  runTest({1, 2, 3, 4, 5, 6}, {2, 1, 4, 3, 6, 5});

  return 0;
}
