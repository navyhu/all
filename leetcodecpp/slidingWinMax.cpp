#include <vector>
#include <deque>

using namespace std;

class Solution
{
	public:
		vector<int> maxSlideingWindow(vector<int>& nums, int k)
		{
			if (nums.empty() || k <= 1)
			  return nums;

			vector<int> result;

			// used to record the first element of the window
			vector<int>::iterator winFirst = nums.begin();

			// deque to record elements,
			// bigger values are stored in begin( from start),
			// smaller values are stored in the rbegin(from end),
			// so the 'begin' one is the biggest one of the window,
			// we should erase 
			deque<int> myDeque;
			int beginCnt = 1;
			int rbeginCnt = 0;

			// push back the 1st element
			myDeque.push_back(*nums.begin());

			for (vector<int>::iterator it = nums.begin() + 1; 
						it != nums.end();
						it++)
			{
				deque<int> begin = myDeque.begin();
				deque<int> rbegin = myDeque.rbegin;

				if (*it >= begin)
				  myDeque.push_front(*it);
				else
				  myDeque.push_back(*it);

				if (count >= k)
				{
				}
			}
		}
};
