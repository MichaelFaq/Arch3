#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

//#include <thread>
#include <pthread.h>
#include <map>

using namespace std;

vector<vector<int>> indexParts;
vector<string> parts;
//vector<string> res;
map <string, bool> res;
string s = "ccccdaaaacbbbbaccccaaa", subs = "aaa*bbb*ccc";
int lenLast = 0;

//vector<int> SearchIndexVect(string ss, string subss);
void ThreadSearchIndexVect(int numb, string ss);
bool SearchElement(string ss, string subss);
void FindMatchIndexes();
void DelSimEl();
