#include <iostream>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Merge2SortedList {
public:
  ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    ListNode *head = NULL;
    ListNode *tail = NULL;
    ListNode *smaller = NULL;

    while (l1 != NULL || l2 != NULL) {
      if (l1 == NULL) {
	smaller = l2;
	l2 = l2->next;
      } else if (l2 == NULL) {
	smaller = l1;
	l1 = l1->next;
      } else if (l1->val < l2->val) {
	smaller = l1;
	l1 = l1->next;
      } else {
	smaller = l2;
	l2 = l2->next;
      }

      if (tail) {
	tail->next = smaller;
	tail = smaller;
      } else {
	head = tail = smaller;
      }
    }

    return head;
  }

  ListNode *mergeTwoLists2(ListNode *l1, ListNode *l2) {
    ListNode *head = new ListNode(-1); //make the head and tail not NULL
    ListNode *tail = head;
    ListNode *smaller = NULL;

    while (l1 && l2) {
      if (l1->val < l2->val) {
	tail->next = l1;
	l1 = l1->next;
      } else {
	tail->next = l2;
	l2 = l2->next;
      }

      tail = tail->next;
    }

    if (l1)
      tail->next = l1;

    if (l2)
      tail->next = l2;

    tail = head;
    head = head->next;
    delete tail;

    return head;
  }
};

#define MERGE2SORTEDLIST_H
#ifdef MERGE2SORTEDLIST_H

int main() {
  Merge2SortedList merge;
  merge.mergeTwoLists(NULL, NULL);
}

#endif //MERGE2SORTEDLIST_H
