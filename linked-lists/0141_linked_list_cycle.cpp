/*
 * Problem: 141. Linked List Cycle
 * Link: https://leetcode.com/problems/linked-list-cycle/
 * Difficulty: Easy
 *
 * Description:
 * Given head, the head of a linked list, determine if the linked list has a
 * cycle in it. Return true if there is a cycle in the linked list. Otherwise,
 * return false.
 *
 * Example:
 * Input: head = [3,2,0,-4], pos = 1
 * Output: true
 * Explanation: There is a cycle in the linked list, where the tail connects to
 * the 1st node.
 *
 * Constraints:
 * - The number of nodes in the list is in the range [0, 10^4].
 * - -10^5 <= Node.val <= 10^5
 * - pos is -1 or a valid index in the linked-list.
 */

#include <iostream>
#include <unordered_map>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  /*
   * Approach 1: Hash Map
   *
   * Key Insight: If we visit the same node twice, there's a cycle.
   * Use a hash map to track visited nodes. If we encounter a node already
   * in the map, we've found a cycle.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(n)
   */
  bool hasCycleHashMap(ListNode *head) {
    unordered_map<ListNode *, bool> visited;
    ListNode *current = head;
    while (current != NULL) {
      if (visited[current] == true) return true;
      visited[current] = true;
      current = current->next;
    }

    return false;
  }

  /*
   * Approach 2: Floyd's Cycle Detection (Two Pointers)
   *
   * Key Insight: If there's a cycle, a fast pointer (moves 2 steps) will
   * eventually catch up to a slow pointer (moves 1 step). Think of it like
   * two runners on a circular track - the faster one will lap the slower one.
   *
   * Time Complexity: O(n)
   * Space Complexity: O(1)
   */
  bool hasCycle(ListNode *head) {
    ListNode *slow_pointer = head, *fast_pointer = head;
    while (fast_pointer != NULL && fast_pointer->next != NULL) {
      slow_pointer = slow_pointer->next;
      fast_pointer = fast_pointer->next->next;
      if (slow_pointer == fast_pointer) return true;
    }

    return false;
  }
};

// ============== Test Cases ==============
int main() {
  Solution solution;

  // Test Case 1: Cycle exists
  ListNode *head1 = new ListNode(3);
  head1->next = new ListNode(2);
  head1->next->next = new ListNode(0);
  head1->next->next->next = new ListNode(-4);
  head1->next->next->next->next = head1->next; // cycle to node 2
  cout << "Test 1: " << (solution.hasCycle(head1) ? "true" : "false")
       << " (Expected: true)" << endl;

  // Test Case 2: No cycle
  ListNode *head2 = new ListNode(1);
  head2->next = new ListNode(2);
  cout << "Test 2: " << (solution.hasCycle(head2) ? "true" : "false")
       << " (Expected: false)" << endl;

  // Test Case 3: Single node, no cycle
  ListNode *head3 = new ListNode(1);
  cout << "Test 3: " << (solution.hasCycle(head3) ? "true" : "false")
       << " (Expected: false)" << endl;

  return 0;
}
