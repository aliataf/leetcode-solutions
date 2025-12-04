/*
 * Problem: 83. Remove Duplicates from Sorted List
 * Link: https://leetcode.com/problems/remove-duplicates-from-sorted-list/
 * Difficulty: Easy
 *
 * Description:
 * Given the head of a sorted linked list, delete all duplicates such that each
 * element appears only once. Return the linked list sorted as well.
 *
 * Example:
 * Input: head = [1,1,2]
 * Output: [1,2]
 *
 * Input: head = [1,1,2,3,3]
 * Output: [1,2,3]
 *
 * Constraints:
 * - The number of nodes in the list is in the range [0, 300].
 * - -100 <= Node.val <= 100
 * - The list is guaranteed to be sorted in ascending order.
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
   * Approach: Linear Traversal
   *
   * Strategy:
   * 1. Traverse the list using a pointer `tmp`.
   * 2. Compare the current node's value with the next node's value.
   * 3. If they are the same, bypass the next node (delete duplicate).
   * 4. If they are different, move the pointer forward.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(1)
   */
  ListNode *deleteDuplicates(ListNode *head) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode *tmp = head;
    ListNode *tmpNext = head->next;
    while (tmpNext != nullptr) {
      if (tmp->val == tmpNext->val) {
        tmp->next = tmpNext->next;
        tmpNext = tmpNext->next;
      } else {
        tmp = tmp->next;
        tmpNext = tmpNext->next;
      }
    }

    return head;
  }
};

// ============== Test Cases ==============
// Helper to print list
void printList(ListNode *head) {
  cout << "[";
  while (head) {
    cout << head->val;
    if (head->next) cout << ",";
    head = head->next;
  }
  cout << "]" << endl;
}

// Helper to create list
ListNode *createList(const vector<int> &vals) {
  if (vals.empty()) return nullptr;
  ListNode *head = new ListNode(vals[0]);
  ListNode *curr = head;
  for (size_t i = 1; i < vals.size(); ++i) {
    curr->next = new ListNode(vals[i]);
    curr = curr->next;
  }
  return head;
}

int main() {
  Solution solution;

  // Test Case 1
  ListNode *head1 = createList({1, 1, 2});
  ListNode *result1 = solution.deleteDuplicates(head1);
  cout << "Test 1: ";
  printList(result1);
  // Expected: [1,2]

  // Test Case 2
  ListNode *head2 = createList({1, 1, 2, 3, 3});
  ListNode *result2 = solution.deleteDuplicates(head2);
  cout << "Test 2: ";
  printList(result2);
  // Expected: [1,2,3]

  // Test Case 3
  ListNode *head3 = createList({});
  ListNode *result3 = solution.deleteDuplicates(head3);
  cout << "Test 3: ";
  printList(result3);
  // Expected: []

  return 0;
}
