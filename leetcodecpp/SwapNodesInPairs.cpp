#include <iostream>
using namespace std;


// Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class SwapNodesInPairs {
public:
    ListNode *swapPairs(ListNode *head) {
      ListNode *pre = head;
      ListNode *cur = head;
      ListNode *post = NULL;

      //swap first pair
      if (cur && cur->next) {
	if (cur->next->next)
	  post = cur->next->next;
	head = cur->next;
	head->next = cur;
	cur->next = post;
	pre = cur;
      } else {
	return head;
      }

      //swap left nodes
      while (cur->next && cur->next->next) {
	cur = cur->next;
	post = cur->next->next;

	pre->next = cur->next;
	pre->next->next = cur;
	cur->next = post;
	pre = cur;
      }

      return head;
    }
};
