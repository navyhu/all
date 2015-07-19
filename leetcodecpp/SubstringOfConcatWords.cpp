#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

struct stringC {
  string str;
  int idx;
};

class SubstringOfConcatWords {
  public:
  vector<int> findSubstring(string S, vector<string> &L) {
    typedef vector<string>::size_type vtype;
    typedef string::size_type stype;

    vtype count = L.size();
    vector<int> result;
    if (count < 1)
      return result;

    stype len = L[0].size();
    stype sLen = S.size();
    if (sLen < len * count)
      return result;

    map<string, int> wordCountMap;
    for (vtype i = 0;i < count;i++) {
      map<string, int>::iterator itMap = wordCountMap.find(L[i]);
      if (itMap != wordCountMap.end()) {
	itMap->second++;
      } else {
	wordCountMap[L[i]] = 1;
      }
    }

    for (stype i = 0;i <= sLen - len*count;i++) {
      map<string, int> wordMap = wordCountMap;
      bool isMatch = true;
      for (stype j = i;j <= i + len*count - len;j += len) {
	string subs = S.substr(j, len);
	map<string, int>::iterator itMap = wordMap.find(subs);
	if (itMap == wordMap.end() || itMap->second == 0) {
	  isMatch = false;
	  break;
	} else {
	  itMap->second--;
	}
      }
      if (isMatch)
	result.push_back(i);
    }

    return result;
  }

    vector<int> findSubstring2(string S, vector<string> &L) {
      typedef vector<string>::size_type vtype;
      typedef string::size_type stype;

      vtype count = L.size();
      vector<int> result;
      if (count < 1)
	return result;

      stype len = L[0].size();
      stype sLen = S.size();
      if (sLen < len * count)
	return result;

      for (string::iterator it = S.begin();it != S.end() - len * count;++it) {
	vector<string>::iterator vit = L.begin();
	for (string::iterator cur = it;cur != S.end() - len;cur = cur + len) {
	  if (!hContainedInVector(cur, L, vit, len)) {
	    break;
	  }
	  vit++;
	} //for

	if (vit == L.end())
	  result.push_back(it - S.begin());
      } //for

      return result;
    }

private:
  bool hContainedInVector(string::iterator sit,
			  vector<string> &vec,
			  vector<string>::iterator vit,
			  string::size_type len) {
    for (vector<string>::iterator it = vit;it != vec.end();++it) {
      if (hCompString(sit, it->begin(), len)) {
	swap(*it, *vit);
	return true;
      }
    }

    return false;
  }

  bool hCompString(string::iterator lhi,
		  string::iterator rhi,
		  string::size_type len) {
    for (string::size_type i = 0;i < len;i++) {
      if (*lhi != *rhi)
	return false;
      lhi++;
      rhi++;
    }

    return true;
  }
};


#define SUBSTRINGOFCONCATWORDS
#ifdef  SUBSTRINGOFCONCATWORDS
int main() {
  //string S = "barfoothefoobarman";
  string S = "a";
  vector<string> L;
  //string Strings[] = {"foo", "bar"};
  string Strings[] = {"a"};
  int len = sizeof(Strings)/sizeof(string);
  for (int i = 0;i < len;i++) {
    L.push_back(Strings[i]);
  }
  
  SubstringOfConcatWords sub;
  
  vector<int> result = sub.findSubstring(S, L);

  for (int i = 0;i < result.size();i++)
    cout<<result[i]<<" ";
  cout<<endl;
}
#endif
