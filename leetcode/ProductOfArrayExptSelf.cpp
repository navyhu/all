#include <vector>
using namespace std;

class Solution
{
	public vector<int> productExceptSelf(vector<int>& nums)
	{
		vector<int> productBeforeSelf;
		vector<int> productAfterSelf;

		int productBefore = 1;
		int productAfter = 1;

		productBeforeSelf.push_back(productBefore);
		productAfterSelf.push_back(productAfter);

		vector<int>::size_type len = nums.size();
		for (vector<int>::size_type front = 0;front < len - 1;front++)
		{
			vector<int>::size_type back = len - front - 1;

			productBefore *= nums[front];
			productAfter *= nums[back];

			productBeforeSelf.push_back(productBefore);
			productAfterSelf.push_back(productAfter);
		}

		for (vector<int>::size_type i = 0;i < len;i++)
		{
			productBeforeSelf[i] *= productAfterSelf[len - i - 1];
		}

		return productBeforeSelf;
	}
};
