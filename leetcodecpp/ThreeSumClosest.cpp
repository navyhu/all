#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class ThreeSumClosest
{
public:
    int threeSumClosest(vector<int> &num, int target) {
    	//sort the list
    	sort(num.begin(), num.end());
    	for (int i = 0;i < num.size();i++) {
    			cout<<num[i]<<" ";
    	}
    	cout<<endl;

    	typedef vector<int>::size_type stype;
    	stype len = num.size();
    	int resultSum = num[0] + num[1] + num[2];
    	unsigned int result = abs(resultSum - target); //init value of result, used to compare

    	stype upper = len;
    	int first = num[0] - 1; //make it different with num[0]
    	for (stype i = 0;i < upper - 2;i++) {
    		if (first == num[i])
    			continue;
    		first = num[i];

    		int second = num[i + 1] - 1; //make it different with num[i + 1]
    		for (stype j = i + 1;j < upper - 1;j++) {
    			if (second == num[j])
    				continue;
    			second = num[j];

    			int delta = target - first - second; //the third number should be closest to delta
    			int third = num[upper - 1] - 1; //make it different with num[upper - 1]
    			stype k = upper - 1;
    			for (k = upper - 1;k > j;k--) {
    				//find the closest numbers with delta
    				if (num[k] < delta) {
    					break;
    				}
    			}
    			if (k == j)
    				k++;
    			//num[k] should be the closest smaller number than delta
    			unsigned int tmpResult = abs(delta - num[k]);
    			if (tmpResult < result) {
    				result = tmpResult;
    				resultSum = target - delta + num[k];
    			}
    			if (k != upper - 1) {
    				tmpResult = abs(delta - num[k + 1]);
    				if (tmpResult < result) {
    					result = tmpResult;
    					resultSum = target - delta + num[k + 1];
    				}

    				if (j == i + 1)
    					upper = k + 1;
    			}

    			if (k == j + 1)
    				break;
    		}
    	}

    	cout<<resultSum<<endl;

    	return resultSum;
    }
};

#define THREESUMCLOSEST_H
#ifdef THREESUMCLOSEST_H

int main()
{
	vector<int> num;
	//int nums[] = {-1, -2, -3, -5, 0, 5, 7, 2, 1, 0, 0, 0};
	//int nums[] = {-4,-1,-4,0,2,-2,-4,-3,2,-3,2,3,3,-4};
	int nums[] = {1,2,4,8,16,32,64,128};
	int target = 82;
	int len = sizeof(nums)/sizeof(int);
	for (int i = 0;i < len;i++) {
		num.push_back(nums[i]);
		cout<<num[i]<<" ";
	}
	cout<<endl;

	ThreeSumClosest three;
	three.threeSumClosest(num, target);

	while(target) {
		cin>>target;
		three.threeSumClosest(num, target);
	}
}
#endif //THREESUMCLOSEST_H
