#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

class ReMatching
{
public:
    bool isMatch(const char *s, const char *p) {
    	/*if (*p == NULL || *s == NULL)
    		return false;
*/
    	if (*p == '\0') {
    		if (*s == '\0')
    			return true;
    		return false;
    	}

    	if (*p == '*')
    		return false;

    	if (*p == '.') {
    		if (*(p + 1) == '*') {
    			for (const char *temp = s; ; ++temp) {
    				bool match = isMatch(temp, p + 2);
    				if (match) return true;
    				if (*temp == '\0') return false;
    			}
    		} else {
    			if (*s == '\0')
    				return false;
    			else
    				return isMatch(s + 1, p + 1);
    		}
    	} else {
    		if (*(p + 1) == '*') {
    			for (const char *temp = s; ; ++temp) {
    				bool match = isMatch(temp, p + 2);
    				if (match) return true;
    				if (*temp != *p) return false;
    			}
    		} else {
    			if (*p == *s)
    				return isMatch(s + 1, p + 1);
    			else
    				return false;
    		}
    	}

    	return false;
    }
};

//#define REMATCHING_H
#ifdef REMATCHING_H

int main()
{
	string s("acaabbaccbbacaabbbb");

	ReMatching ma;

	string  p("a*.*b*.*a*aa*a*");

	cout<<ma.isMatch(s.c_str(), p.c_str());

	cout<<ma.isMatch("ab", ".*")<<endl;
	cout<<ma.isMatch("aa", "a*")<<endl;
	cout<<ma.isMatch("aab", "c*a*b")<<endl;

	/*while(ci[0] != '0') {
		cout<<ma.isMatch(s, ci.c_str());
		cin>>ci;
	}*/
}
#endif //REMATCHING_H
