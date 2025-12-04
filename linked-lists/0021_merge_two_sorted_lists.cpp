/*
 * Problem: 21. Merge Two Sorted Lists
 * Link: https://leetcode.com/problems/merge-two-sorted-lists/
 * Difficulty: Easy
 *
 * Description:
 * You are given the heads of two sorted linked lists list1 and list2.
 * Merge the two lists in a one sorted list. The list should be made by splicing
 * together the nodes of the first two lists. Return the head of the merged
 * linked list.
 *
 * Example:
 * Input: list1 = [1,2,4], list2 = [1,3,4]
 * Output: [1,1,2,3,4,4]
 *
 * Input: list1 = [], list2 = []
 * Output: []
 *
 * Input: list1 = [], list2 = [0]
 * Output: [0]
 *
 * Constraints:
 * - The number of nodes in both lists is in the range [0, 50].
 * - -100 <= Node.val <= 100
 * - Both list1 and list2 are sorted in non-decreasing order.
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
   * Approach: Iterative
   * Create a new head for the result list. Iterate through both lists,
   * comparing values and appending the smaller value to the result list. If one
   * list becomes empty, append the rest of the other list.
   *
   * Time Complexity: O(n + m)
   * Space Complexity: O(1) (ignoring the new nodes created in this specific
   * implementation)
   */
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;

    ListNode *head;
    if (list1->val <= list2->val) {
      head = new ListNode(list1->val);
      list1 = list1->next;
    } else {
      head = new ListNode(list2->val);
      list2 = list2->next;
    }
    ListNode *tail = head;

    while (list1 != nullptr || list2 != nullptr) {
      if (list1 == nullptr) {
        tail->next = list2;
        break;
      }

      if (list2 == nullptr) {
        tail->next = list1;
        break;
      }

      if (list1->val <= list2->val) {
        tail->next = new ListNode(list1->val);
        tail = tail->next;
        list1 = list1->next;
      } else {
        tail->next = new ListNode(list2->val);
        tail = tail->next;
        list2 = list2->next;
      }
    }

    return head;
  }
};

// ============== Test Cases ==============
// Helper to create a list from a vector
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

// Helper to print a list
void printList(ListNode *head) {
  cout << "[";
  while (head) {
    cout << head->val << (head->next ? "," : "");
    head = head->next;
  }
  cout << "]" << endl;
}

int main() {
  Solution solution;

  // Test Case 1
  ListNode *l1_1 = createList({1, 2, 4});
  ListNode *l1_2 = createList({1, 3, 4});
  ListNode *result1 = solution.mergeTwoLists(l1_1, l1_2);
  cout << "Test 1: ";
  printList(result1);
  // Expected: [1,1,2,3,4,4]

  // Test Case 2
  ListNode *l2_1 = createList({});
  ListNode *l2_2 = createList({});
  ListNode *result2 = solution.mergeTwoLists(l2_1, l2_2);
  cout << "Test 2: ";
  printList(result2);
  // Expected: []

  // Test Case 3
  ListNode *l3_1 = createList({});
  ListNode *l3_2 = createList({0});
  ListNode *result3 = solution.mergeTwoLists(l3_1, l3_2);
  cout << "Test 3: ";
  printList(result3);
  // Expected: [0]

  return 0;
}
