#include <iostream>
using namespace std;

class RemoveElement {
public:
    int removeElement(int A[], int n, int elem) {
      if (n < 1)
	return n;
      int count = 1;
      for (int i = 0;i < n;i++) {
	if (A[i] == elem) {
	  //swap it with the last element which is not elem
	  int idx = n - count;
	  if (i <= idx)
	    count++;
	  while (idx > i && A[idx] == elem) {
	    count++;
	    idx--;
	  }
	  if (i >= idx)
	    break;
	  swap(A[i], A[idx]);
	}
      }

      return n - count + 1;
    }
};
