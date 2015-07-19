#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class ReverseInteger
{
public:
	int reverse(int x)
	{
		unsigned int absX = abs(x);
		long long result = 0;

		while (absX > 0)
		{
			result *= 10;
			result += absX%10;
			absX /= 10;
		}

		if (result > 0xFFFFFFFF)
			result = 0;
		else if (x < 0)
			result = -result;

		return result;
	}
};

//#define REVERSEINTEGER_H
#ifdef REVERSEINTEGER_H

int main()
{
	int x = 1534236469;
	int xx = -0x7FFFFFFF;
	int xxx = 0xFFFFFFFF;
	ReverseInteger reverse;
	cout<<x<<endl<<reverse.reverse(x)<<endl;
	cout<<xx<<endl<<reverse.reverse(xx)<<endl;
	cout<<xxx<<endl<<reverse.reverse(xxx)<<endl;

	int ci;
	cin>>ci;
}
#endif //REVERSEINTEGER_H
