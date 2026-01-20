/*
 * Problem: 19. Remove Nth Node From End of List
 * Link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
 * Difficulty: Medium
 *
 * Description:
 * Given the head of a linked list, remove the nth node from the end of the list
 * and return its head.
 *
 * Example:
 * Input: head = [1,2,3,4,5], n = 2
 * Output: [1,2,3,5]
 *
 * Input: head = [1], n = 1
 * Output: []
 *
 * Input: head = [1,2], n = 1
 * Output: [1]
 *
 * Constraints:
 * - The number of nodes in the list is sz.
 * - 1 <= sz <= 30
 * - 0 <= Node.val <= 100
 * - 1 <= n <= sz
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
   * Approach: Two-Pass Algorithm (Calculate Size)
   *
   * Key Insight: To find the nth node from the end, we can first determine the
   * length of the list, L. Then, the problem becomes removing the (L - n + 1)th
   * node from the beginning.
   *
   * Strategy:
   * 1. Traverse the list to calculate its total size.
   * 2. Handle the special case where we need to remove the head (size - n ==
   * 0).
   * 3. Traverse the list again to the node just before the target node (index
   * size - n).
   * 4. Update the next pointer of the predecessor to skip the target node.
   *
   * Time Complexity: O(L) - we traverse the list twice.
   * Space Complexity: O(1) - we only use a few pointers.
   */
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    if (head == nullptr || head->next == nullptr) return nullptr;

    int size = 0;
    ListNode *temp = head;
    while (temp != nullptr) {
      size++;
      temp = temp->next;
    }

    if (size - n == 0) return head->next;

    temp = head;
    int index = 1;
    while (temp->next != nullptr) {
      if (index == size - n) {
        temp->next = temp->next->next;
        break;
      } else {
        temp = temp->next;
      }
      index++;
    }

    return head;
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

void runTest(vector<int> vals, int n, vector<int> expectedVals) {
  Solution solution;
  ListNode *head = createList(vals);
  cout << "Input: head = ";
  printList(head);
  cout << ", n = " << n << endl;

  ListNode *result = solution.removeNthFromEnd(head, n);
  cout << "Output: ";
  printList(result);

  // Simple verification (could be more robust)
  cout << "Expected: ";
  ListNode *expected = createList(expectedVals);
  printList(expected);
  cout << endl;
}

int main() {
  runTest({1, 2, 3, 4, 5}, 2, {1, 2, 3, 5});
  runTest({1}, 1, {});
  runTest({1, 2}, 1, {1});
  runTest({1, 2}, 2, {2}); // Removing head

  return 0;
}
