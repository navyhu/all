#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class StrStrImpl {
public:
    int strStr(char *haystack, char *needle) {
      int len = strlen(haystack) - strlen(needle);

      for (int i = 0;i <= len;i++) {
	char *p = haystack + i;
	char *q = needle;
	while(*q && *p == *q) {
	  p++;
	  q++;
	}

	if (*q == 0)
	  return i;
      }

      return -1;
    }
};

#define STRSTRIMPL_H
#ifdef STRSTRIMPL_H

int main() {
  StrStrImpl str;
  int result = str.strStr("", "");

  cout<<result<<endl;
}

#endif //STRSTRIMPL_H
