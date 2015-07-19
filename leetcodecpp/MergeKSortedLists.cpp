#include <iostream>
#include <vector>
#include <set>
#include <multiset>
#include <queue>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct CompareListNode {
  bool operator() (const ListNode *lhs, const ListNode *rhs) const {
    if (lhs && rhs)
      return (lhs->val < rhs->val);

    return false;
  }
};

class MergeKSortedLists {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
      ListNode *result = new ListNode(-1); //dummy node
      ListNode *tail = result;
      multiset<ListNode *, CompareListNode> listHeads; //store each list head in order

      for (vector<ListNode *>::size_type i = 0;i < lists.size();i++) {
	if (lists[i]) {
	  listHeads.insert(lists[i]);
	  lists[i] = lists[i]->next;
	}
      }

      while (!listHeads.empty()) {
	multiset<ListNode *, CompareListNode>::iterator it = listHeads.begin();
	ListNode *cur = *it;
	listHeads.erase(it);

	tail->next = cur;
	tail = tail->next;
	cur = cur->next;

	if (cur)
	  listHeads.insert(cur);
      }

      //delete dummy node
      tail = result;
      result = result->next;
      delete tail;

      return result;
    }

public:
    ListNode *mergeKLists2(vector<ListNode *> &lists) {
      ListNode *result = new ListNode(-1); //dummy node
      ListNode *tail = result;
      priority_queue<ListNode *, vector<ListNode *>, CompareListNode> pQueue;
      //multiset<ListNode *, CompareListNode> listHeads; //store each list head in order

      for (vector<ListNode *>::size_type i = 0;i < lists.size();i++) {
	if (lists[i]) {
	  pQueue.push(lists[i]);
	  //listHeads.insert(lists[i]);
	  lists[i] = lists[i]->next;
	}
      }

      while (!pQueue.empty()) {
	//multiset<ListNode *, CompareListNode>::iterator it = listHeads.begin();
	ListNode *cur = pQueue.top();
	pQueue.pop();

	tail->next = cur;
	tail = tail->next;
	cur = cur->next;

	if (cur)
	  pQueue.push(cur);
      }

      //delete dummy node
      tail = result;
      result = result->next;
      delete tail;

      return result;
    }
};

#define MERGEKSORTEDLISTS_H
#ifdef MERGEKSORTEDLISTS_H

int main() {
  MergeKSortedLists merge;
  //merge.mergeKLists(NULL);
}

#endif //MERGEKSORTEDLISTS_H
