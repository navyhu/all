#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class RemoveNthNodeReverse
{
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    ListNode *first = head;
    ListNode *second = head;
    ListNode *cur = head;
    int count = 0;
    int interval = n + 1;

    if (n < 1 || head == NULL)
      return head;

    if (n == 1)
      return hRemoveTail(head);

    while (cur) {
      count++;
      cur = cur->next;
      if (count == interval) {
	first = second;
	second = cur;
	count = 0;
      }
    }

    if (second == head) {
      if (count < n)
	return head;
      else
	return hRemoveHead(head);
    }

    //move to the node before the target
    for (int i = 0;i < count;i++) {
      first = first->next;
    }
    
    return hRemoveNextNode(head, first);
  }

  ListNode *hRemoveHead(ListNode *head) {
    ListNode *cur = head;
    if (head) {
      head = head->next;
      delete cur;
    }
    return head;
  }

  ListNode *hRemoveTail(ListNode *head) {
    ListNode *cur = head;
    if (head == NULL)
      return head;

    if (head->next == NULL) {
      delete head;
      return NULL;
    }

    while(cur->next->next) {
      cur = cur->next;
    }

    return hRemoveNextNode(head, cur);
  }

  ListNode *hRemoveNextNode(ListNode *head, ListNode *preRemove) {
    if (preRemove == NULL || preRemove->next == NULL)
      return head;

    ListNode *removed = preRemove->next;
    preRemove->next = removed->next;
    delete removed;

    return head;
  }

  ListNode *createList(int num[], int n) {
    ListNode *head;
    ListNode *end;
    if (n > 0) {
      int number = num[0];
      head = new ListNode(num[0]);
      end = head;
    } else {
      return head;
    }
    for (int i = 1;i < n;i++) {
      end->next = new ListNode(num[i]);
      end = end->next;
    }

    return head;
  }

  void printList(ListNode *head) {
    while (head) {
      cout<<head->val<<" ";
      head = head->next;
    }
    cout<<endl;
  }
};

#define REMOVENTHNODEREVERSE_H
#ifdef REMOVENTHNODEREVERSE_H

int main()
{
  int num[] = {1, 2, 3, 4, 5, 6, 7};
  int n = 3;
  int len = sizeof(num)/sizeof(num[0]);
  RemoveNthNodeReverse remove;
  ListNode *head = remove.createList(num, len);
  /*  remove.printList(head);

  remove.removeNthFromEnd(head, n);
  remove.printList(head);*/

  while(n) {
    remove.printList(head);
    head = remove.removeNthFromEnd(head, n);
    remove.printList(head);
    cin>>n;
  }
}
#endif //REMOVENTHNODEREVERSE_H
