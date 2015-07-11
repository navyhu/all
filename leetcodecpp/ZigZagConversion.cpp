#include <iostream>
#include <string>

using namespace std;

class ZigZagConversion
{
public:
	string convert(string s, int nRows)
	{
		if (nRows <= 1)
		{
			return s;
		}

		string::size_type len = s.size();
		if (len < 3 || len <= nRows)
		{
			return s;
		}

		string result = "";

		string::size_type lIntervalOne = nRows*2 - 2;
		string::size_type lIntervalTwo = 0;
		for (string::size_type i = 0;i < nRows;i++)
		{
			string::size_type index = i;
			result.push_back(s[index]);

			while (index < len)
			{
				if (lIntervalOne > 0)
				{
					index += lIntervalOne;
					if (index < len)
						result.push_back(s[index]);
					else
						break;
				}
				if (lIntervalTwo > 0)
				{
					index += lIntervalTwo;
					if (index < len)
						result.push_back(s[index]);
					else
						break;
				}
			}
			lIntervalOne -= 2;
			lIntervalTwo += 2;
		}

		return result;
	}
};

//#define ZIGZAGCONVERSION_H
#ifdef ZIGZAGCONVERSION_H

int main()
{
	string test = "PAYPALISHIRING";
	int rows = 3;
	ZigZagConversion zigzag;

	cout<<test<<endl;
	string result = zigzag.convert(test, rows);
	cout<<result<<endl;

	int ci;
	cin>>ci;
}
#endif //ZIGZAGCONVERSION_H
