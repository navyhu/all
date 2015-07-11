#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

class LongestCommonPrefix
{
public:
    string longestCommonPrefix(vector<string> &strs) {
    	typedef vector<string>::size_type stype;

    	stype num = strs.size();
    	if (num == 0)
    		return string("");

    	if (num == 1)
    		return strs[0];

    	string result;
    	stype len = strs[0].size();
    	for (stype i = 0;i < len;i++) {
    		for (stype j = 1;j < num;j++) {
    			if ((strs[j].size() <= i) || (strs[j][i] != strs[0][i])) {
    				return result;
    			}
    		}

    		result.push_back(strs[0][i]);
    	}

    	return result;
    }
};

//#define LONGESTCOMMONPREFIX_H
#ifdef LONGESTCOMMONPREFIX_H

int main()
{
}
#endif //LONGESTCOMMONPREFIX_H
