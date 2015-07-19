#include <iostream>

using namespace std;

class SearchInRotatedSortedArray {
public:
  int search(int A[], int n, int target) {
    if (n < 1)
      return -1;

    if (n == 1) {
      if (A[0] == target)
	return 0;
      return -1;
    }

    if (A[0] < A[n - 1])
      return binary_search(A, 0, n, target);

    if (target >= A[0])
      return left_search(A, 0, n, target);
    if (target <= A[n - 1])
      return right_search(A, 0, n, target);

    return -1;
  }

private:
  int binary_search(int A[], int start, int end, int target) {
    if (start >= end)
      return -1;

    int middle = (start + end) / 2;
    if (A[middle] == target)
      return middle;

    if (A[middle] > target)
      return binary_search(A, start, middle, target);

    return binary_search(A, middle + 1, end, target);
  }

  int left_search(int A[], int start, int end, int target) {
    if (start >= end)
      return -1;

    int middle = (start + end) / 2;
    if (A[middle] == target)
      return middle;

    if (A[middle] < target) {
      if (end - 1 < 0)
	return -1;

      if (A[middle] <= A[end - 1])
	return left_search(A, start, middle, target);
      else if (A[middle] > A[end - 1])
	return left_search(A, middle + 1, end, target);
    }

    return binary_search(A, start, middle, target);
  }

  int right_search(int A[], int start, int end, int target) {
    if (start >= end)
      return -1;

    int middle = (start + end) / 2;
    if (A[middle] == target)
      return middle;

    if (A[middle] > target) {
      if (A[middle] >= A[start] && middle + 1 < end && A[middle + 1] > target)
	return right_search(A, middle + 1, end, target);
      if (A[middle] < A[start])
	return right_search(A, start, middle, target);
    }

    return binary_search(A, middle + 1, end, target);
  }
};

#define SEARCHINROTATEDSORTEDARRAY_H
#ifdef SEARCHINROTATEDSORTEDARRAY_H
int main() {
  int A[] = {3, 4, 5, 6, -2, 1, 2};
  //int A[] = {2, 3};
  int n = sizeof(A)/sizeof(int);
  int target = 9;
  SearchInRotatedSortedArray search;
  int result = search.search(A, n, target);
  cout<<result<<endl;
  return 0;
}
#endif //SEARCHINROTATEDSORTEDARRAY_H
