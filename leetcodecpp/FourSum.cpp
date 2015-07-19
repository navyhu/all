#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class FourSum
{
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        typedef vector<int>::size_type stype;
	stype len = num.size();
	vector<vector<int> > result;

	//sort the list
	sort(num.begin(), num.end());
	for (stype i = 0;i < len;i++) {
	  cout<<num[i]<<" ";
	}
	cout<<endl;

	int first = num[0] - 1; //make it different with num[0]
	int endIdx = len; //the end index
	for (stype i = 0;i < endIdx - 3;i++) {
	  if (first == num[i])
	    continue;
	  first = num[i];
	  
	  int second = num[endIdx - 1] - 1; //make it different with num[endIdx - 1];
	  for (stype j = endIdx - 1;j > i + 2;j--) {
	    if (second == num[j])
	      continue;
	    second = num[j];

	    int third = num[j - 1] - 1; //make it different with num[j - 1]
	    for (stype k = j - 1;k > i + 1;k--) {
	      if (third == num[k])
		continue;
	      third = num[k];

	      int fourth = num[k - 1] - 1; //make it different with num[k - 1]
	      stype h; //for index
	      for (h = k - 1;h > i;h--) {
		if (fourth == num[h])
		  continue;
		fourth = num[h];
		int sum = first + second + third + fourth;
		if (sum < target) {
		  break;
		} else if (sum == target) {
		  hPushBack(result, first, fourth, third, second);
		  //result.push_back(vector<int>{first, fourth, third, second});
		  break;
		}
	      }//end for h

	      if (h == k - 1) {
		if (k == j - 1)
		  endIdx = j + 1;
		break;
	      }
	      /*if (k == j - 1 && h == k - 1) {
		//the 3 numbers are adjacent
		endIdx = j + 1;
		}*/
	    }//end for k
	  }//end for j
	}//end for i

	return result;
    }

private:
  void hPushBack(vector<vector<int> > &result, int a, int b, int c, int d) {
    vector<int> item;
    item.push_back(a);
    item.push_back(b);
    item.push_back(c);
    item.push_back(d);
    result.push_back(item);
  }
};

#define FOURSUM_H
#ifdef FOURSUM_H

int main()
{
    vector<int> num;
    //int nums[] = {-1, -2, -3, -5, 0, 5, 7, 2, 1, 0, 0, 0};
    int nums[] = {-4,-1,-4,0,2,-2,-4,-3,2,-3,2,3,3,-4};
    //int nums[] = {1,2,4,8,16,32,64,128};
    int target = 82;
    int len = sizeof(nums)/sizeof(int);
    for (int i = 0;i < len;i++) {
      num.push_back(nums[i]);
      cout<<num[i]<<" ";
    }
    cout<<endl;
    FourSum four;
    four.fourSum(num, target);

    while(target) {
      cin>>target;
      four.fourSum(num, target);
    }
}
#endif //FOURSUM_H
