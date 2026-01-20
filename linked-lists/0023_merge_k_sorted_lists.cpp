/*
 * Problem: 23. Merge k Sorted Lists
 * Link: https://leetcode.com/problems/merge-k-sorted-lists/
 * Difficulty: Hard
 *
 * Description:
 * You are given an array of k linked-lists lists, each linked-list is sorted in
 * ascending order. Merge all the linked-lists into one sorted linked-list and
 * return it.
 *
 * Example 1:
 * Input: lists = [[1,4,5],[1,3,4],[2,6]]
 * Output: [1,1,2,3,4,4,5,6]
 *
 * Example 2:
 * Input: lists = []
 * Output: []
 *
 * Example 3:
 * Input: lists = [[]]
 * Output: []
 *
 * Constraints:
 * - k == lists.length
 * - 0 <= k <= 10^4
 * - 0 <= lists[i].length <= 500
 * - -10^4 <= lists[i][j] <= 10^4
 * - lists[i] is sorted in ascending order.
 * - The sum of lists[i].length will not exceed 10^4.
 */

#include <iostream>
#include <map>
#include <queue>
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
   * Approach 1: Frequency Map (Using std::map)
   *
   * Strategy:
   * 1. Use a frequency map (ordered by key) to store counts of all values in
   * all lists.
   * 2. Traverse each linked list once to populate the map.
   * 3. Construct a new linked list by iterating through the map in ascending
   * order.
   *
   * Time Complexity: O(N log M) where N is total nodes and M is absolute range
   * or unique count.
   * Space Complexity: O(M) for the map.
   */
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    map<int, int> mp;
    for (ListNode *list : lists) {
      ListNode *temp = list;
      while (temp != nullptr) {
        mp[temp->val]++;
        temp = temp->next;
      }
    }

    if (mp.empty()) return nullptr;

    ListNode *dummy = new ListNode(0);
    ListNode *tail = dummy;
    for (auto &[num, count] : mp) {
      while (count--) {
        tail->next = new ListNode(num);
        tail = tail->next;
      }
    }

    return dummy->next;
  }

  /*
   * Approach 2: Optimized using Priority Queue (Min-Heap)
   *
   * Strategy:
   * 1. Use a min-heap to store the head of each list.
   * 2. Repeatedly extract the smallest node from the heap and add it to the
   * merged list.
   * 3. If the extracted node has a next node, add that next node to the heap.
   *
   * Time Complexity: O(N log k) where N is the total number of nodes and k is
   * the number of lists.
   * Space Complexity: O(k) for the priority queue.
   */
  struct compare {
    bool operator()(ListNode *a, ListNode *b) { return a->val > b->val; }
  };

  ListNode *mergeKListsOptimized(vector<ListNode *> &lists) {
    priority_queue<ListNode *, vector<ListNode *>, compare> pq;

    for (ListNode *list : lists) {
      if (list) pq.push(list);
    }

    ListNode *dummy = new ListNode(0);
    ListNode *tail = dummy;

    while (!pq.empty()) {
      ListNode *top = pq.top();
      pq.pop();

      tail->next = top;
      tail = tail->next;

      if (top->next) pq.push(top->next);
    }

    return dummy->next;
  }
};

// ============== Test Cases ==============
void printList(ListNode *head) {
  if (!head) {
    cout << "[]" << endl;
    return;
  }
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

int main() {
  Solution solution;

  // Test Case 1
  vector<ListNode *> lists1 = {createList({1, 4, 5}), createList({1, 3, 4}),
                               createList({2, 6})};
  cout << "Test 1 (Map Approach): ";
  printList(solution.mergeKLists(lists1));
  // Expected: [1,1,2,3,4,4,5,6]

  // Test Case 2
  vector<ListNode *> lists2 = {createList({1, 4, 5}), createList({1, 3, 4}),
                               createList({2, 6})};
  cout << "Test 1 (Heap Approach): ";
  printList(solution.mergeKListsOptimized(lists2));
  // Expected: [1,1,2,3,4,4,5,6]

  // Test Case 3: Empty lists
  vector<ListNode *> lists3 = {};
  cout << "Test 2: ";
  printList(solution.mergeKLists(lists3));
  // Expected: []

  // Test Case 4: List with empty element
  vector<ListNode *> lists4 = {nullptr};
  cout << "Test 3: ";
  printList(solution.mergeKLists(lists4));
  // Expected: []

  return 0;
}
