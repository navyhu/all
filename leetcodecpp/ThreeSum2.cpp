#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class ThreeSum2
{
};

#define THREESUM2_H
#ifdef THREESUM2_H

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
#endif //THREESUM2_H
