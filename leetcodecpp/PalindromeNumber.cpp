#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class PalindromeNumber
{
public:
    bool isPalindrome(int x) {
    	if (x < 0)
    		return false;

    	int revX = 0;
    	int tempX = x;

    	while (tempX) {
    		revX = revX * 10 + tempX % 10;
    		tempX /= 10;
    	}

    	if (revX == x)
    		return true;

    	return false;
    }
};

//#define PALINDROMENUMBER_H
#ifdef PALINDROMENUMBER_H

int main()
{
	int x = 1534236469;

	PalindromeNumber palindrome;
	cout<<x<<endl<<palindrome.isPalindrome(x)<<endl;

	int ci = 1;
	while (ci) {
		cin>>ci;
		cout<<ci<<endl<<palindrome.isPalindrome(ci)<<endl;
	}
}
#endif //PALINDROMENUMBER_H
