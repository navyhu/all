#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class MedianOf2SortedArrays
{
public:
	/*
	 * 3 situations
	 * 1. A and B have no overlap(All elements in A are smaller than those in B(vise versa))
	 * 2. A contains B(vise versa)
	 * 3. A overlaps with B
	 */
    double findMedianSortedArrays(int A[], int m, int B[], int n)
    {
    	printArray(A, m);
    	printArray(B, n);
    	//no overlap
    	if (A[m - 1] <= B[0])
    		return findMedianNoOverlap(A, m, B, n);
    	else if (B[n - 1] <= A[0])
    		return findMedianNoOverlap(B, n, A, m);

    	//overlap
    	int median = (m + n) / 2;
    	int medianA = m / 2;
    	int medianB = median - medianA;
    	int previousB = medianB - 1;
    	if (previousB < 0)
    		previousB = 0;

    	while(A[medianA] > B[medianB] || A[medianA] < B[previousB])
    	{

    	}
    }

private:
    void printArray(int A[], int m)
	{
    	for (int i = 0;i < m;i++) {
    		cout<<A[i]<<" ";
    	}
    	cout<<endl;
    }

    double findMedianNoOverlap(int A[], int m, int B[], int n)
    {
    	int median = (m + n) / 2;
    	double result = 0;

    	if (median < m)
    		result = A[median];
    	else
    		result = B[median - m];

    	if ((m + n) % 2 != 0)
    	{
    		median--;
    		if (0 < median && median < m)
    			result = (result + A[median]) / 2;
    		else
    			result = (result + B[median - m]) / 2;
    	}

    	return result;
    }
};

//#define MEDIANOF2SORTEDARRAYS_H
#ifdef MEDIANOF2SORTEDARRAYS_H

int main()
{
	int A[] = {1, 2, 3, 5};
	int B[] = {2, 5, 6, 8};
	int m = sizeof(A)/sizeof(int);
	int n = sizeof(B)/sizeof(int);

	MedianOf2SortedArrays median;

	cout<<median.findMedianSortedArrays(A, m, B, n);
}
#endif //MEDIANOF2SORTEDARRAYS_H
