/*
 * Problem: 2. Add Two Numbers
 * Link: https://leetcode.com/problems/add-two-numbers/
 * Difficulty: Medium
 *
 * Description:
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order, and each of their nodes
 * contains a single digit. Add the two numbers and return the sum as a linked
 * list.
 *
 * Example 1:
 * Input: l1 = [2,4,3], l2 = [5,6,4]
 * Output: [7,0,8]
 * Explanation: 342 + 465 = 807
 *
 * Example 2:
 * Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * Output: [8,9,9,9,0,0,0,1]
 *
 * Constraints:
 * - The number of nodes in each linked list is in the range [1, 100]
 * - 0 <= Node.val <= 9
 * - It is guaranteed that the list represents a number that does not have
 * leading zeros
 */

#include <iostream>

using namespace std;

// Definition for singly-linked list
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
   * Approach: Elementary Math (Digit by Digit Addition)
   * Traverse both lists simultaneously, adding corresponding digits along with
   * carry. Create new nodes for the result. Handle remaining nodes and final
   * carry.
   *
   * Time Complexity: O(max(m, n)) - where m, n are lengths of the two lists
   * Space Complexity: O(max(m, n)) - for the result list
   */
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode dummy(0); // Dummy head to simplify edge cases
    ListNode *curr = &dummy;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr || carry != 0) {
      int sum = carry;

      if (l1 != nullptr) {
        sum += l1->val;
        l1 = l1->next;
      }

      if (l2 != nullptr) {
        sum += l2->val;
        l2 = l2->next;
      }

      carry = sum / 10;
      curr->next = new ListNode(sum % 10);
      curr = curr->next;
    }

    return dummy.next;
  }
};

// ============== Helper Functions ==============
ListNode *createList(initializer_list<int> vals) {
  ListNode dummy(0);
  ListNode *curr = &dummy;
  for (int val : vals) {
    curr->next = new ListNode(val);
    curr = curr->next;
  }
  return dummy.next;
}

void printList(ListNode *head) {
  cout << "[";
  while (head != nullptr) {
    cout << head->val;
    if (head->next) cout << ",";
    head = head->next;
  }
  cout << "]" << endl;
}

void deleteList(ListNode *head) {
  while (head != nullptr) {
    ListNode *temp = head;
    head = head->next;
    delete temp;
  }
}

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1: 342 + 465 = 807
  ListNode *l1 = createList({2, 4, 3});
  ListNode *l2 = createList({5, 6, 4});
  ListNode *result1 = solution.addTwoNumbers(l1, l2);
  cout << "Test 1: ";
  printList(result1); // Expected: [7,0,8]
  deleteList(l1);
  deleteList(l2);
  deleteList(result1);

  // Test Case 2: 0 + 0 = 0
  l1 = createList({0});
  l2 = createList({0});
  ListNode *result2 = solution.addTwoNumbers(l1, l2);
  cout << "Test 2: ";
  printList(result2); // Expected: [0]
  deleteList(l1);
  deleteList(l2);
  deleteList(result2);

  // Test Case 3: 9999999 + 9999 = 10009998
  l1 = createList({9, 9, 9, 9, 9, 9, 9});
  l2 = createList({9, 9, 9, 9});
  ListNode *result3 = solution.addTwoNumbers(l1, l2);
  cout << "Test 3: ";
  printList(result3); // Expected: [8,9,9,9,0,0,0,1]
  deleteList(l1);
  deleteList(l2);
  deleteList(result3);

  cout << "All tests passed!" << endl;
  return 0;
}
