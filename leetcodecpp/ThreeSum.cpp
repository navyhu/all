#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class ThreeSum
{
public:
    vector<vector<int> > threeSum(vector<int> &num) {
    	typedef vector<int>::size_type itype;
    	vector<vector<int> > result;

    	sort(num.begin(), num.end());
    	itype len = num.size();
    	if (len < 3)
    		return result;

    	for (int i = 0;i < len;i++) {
    		cout<<num[i]<<" ";
    	}
    	cout<<endl;

    	//find the position of the biggest negative number and positive number
    	int posPos = len - 1;
    	if (num[posPos] < 0)
    		return result;

    	int posNeg = -1;
    	for (itype i = 0;i < len;i++) {
    		if (num[i] >= 0)
    			break;
    		posNeg++;
    	}

    	//no negative number
    	/*if (posNeg == -1) {
    		if (num[0] == 0 && num[1] == 0 && num[2] == 0) {
    			hPushBack(result, 0, 0, 0);
    			//result.push_back(vector<int>{0, 0, 0});
    		}

    		return result;
    	}*/
    	if (len - posNeg > 3) {
    		if (num[posNeg + 1] == 0 && num[posNeg + 2] == 0 && num[posNeg + 3] == 0) {
    			hPushBack(result, 0, 0, 0);
    		}
    	}

    	//one negative with 2 positives
    	int curNeg = 0;
    	int tempPosPos = posPos;
    	for (int i = 0;i <= posNeg;i++) {
    		if (num[i] == curNeg)
    			continue;

    		curNeg = num[i];

    		int first = -1;
    		int second = -1;
    		for (int j = tempPosPos;j > posNeg + 1;j--) {
    			//skip equal numbers
    			if (num[j] == first)
    				continue;
    			first = num[j];

    			//The biggest positive is too big
    			if (first + curNeg > 0) {
    				tempPosPos--;
    				continue;
    			}
    			int sum = 0;
    			second = -1;
    			for (int k = j - 1;k > posNeg;k--) {
    				if (num[k] == second)
    					continue;
    				second = num[k];
    				sum = curNeg + first + second;
    				if (sum == 0) {
    					//result.push_back(vector<int>{curNeg, second, first});
    					hPushBack(result, curNeg, second, first);
    					break;
    				}
    				if (sum < 0)
    					break;
    			}
    		}
    	}

    	//2 negatives with 1 positive
    	int curPos = -1;
    	int startPos = 0;
    	for (int i = posPos;i > posNeg;i--) {
    		if (num[i] == curPos)
    			continue;

    		curPos = num[i];

    		int first = 1;
    		int second = 1;
    		for (int j = startPos;j < posNeg;j++) {
    			//skip equal numbers
    			if (num[j] == first)
    				continue;
    			first = num[j];

    			//The smallest negative is too small
    			if (first + curPos < 0) {
    				startPos++;
    				continue;
    			}
    			int sum = 0;
    			second = 1;
    			for (int k = j + 1;k <= posNeg;k++) {
    				if (num[k] == second)
    					continue;
    				second = num[k];
    				sum = curPos + first + second;
    				if (sum == 0) {
    					//result.push_back(vector<int>{curNeg, second, first});
    					hPushBack(result, first, second, curPos);
    					break;
    				}
    				if (sum > 0)
    					break;
    			}
    		}
    	}

    	for (itype i = 0;i < result.size();i++) {
    		for (itype j = 0;j < result[i].size();j++)
    			cout<<result[i][j]<<" ";
    		cout<<endl;
    	}
    	return result;
    }

private:
    void hPushBack(vector<vector<int> > &result, int a, int b, int c) {
    	vector<int> item;
    	item.push_back(a);
    	item.push_back(b);
    	item.push_back(c);
    	result.push_back(item);
    }
};

//#define THREESUM_H
#ifdef THREESUM_H

int main()
{
	vector<int> num;
	//int nums[] = {-1, -2, -3, -5, 0, 5, 7, 2, 1, 0, 0, 0};
	int nums[] = {-4,-1,-4,0,2,-2,-4,-3,2,-3,2,3,3,-4};
	int len = sizeof(nums)/sizeof(int);
	for (int i = 0;i < len;i++) {
		num.push_back(nums[i]);
		cout<<num[i]<<" ";
	}
	cout<<endl;

	ThreeSum three;
	three.threeSum(num);
}
#endif //THREESUM_H
