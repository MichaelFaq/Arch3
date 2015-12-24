#include "l3.h"

using namespace std;

struct thread_data
{
	int n;
	string s;
};

/*vector<int> SearchIndexVect(string ss, string subss)
{
	vector<int> promV;
	if (subss.empty())
	{
		for (int i = 0; i < ss.size(); i++) promV.insert(promV.end(), i);
	}
	else
	{
		int k = 0;
		while (ss.find(subss) != -1)
		{
			promV.insert(promV.end(), ss.find(subss) + k);
			k = k + ss.find(subss) + 1;
			ss.erase(0, ss.find(subss) + 1);
		}
	}
	return promV;
}

bool SearchElement(string ss, string subss)
{
	bool flag = true;
	while (subss.find("*") != -1)
	{
		indexParts.insert(indexParts.end(), SearchIndexVect(ss, subss.substr(0, subss.find("*"))));
		if (indexParts[indexParts.size() - 1].size() == 0) flag = false;
		lenLast = subss.substr(0, subss.find("*")).length();
		subss.erase(0, subss.find("*") + 1);
	}
	lenLast = subss.length();
	indexParts.insert(indexParts.end(), SearchIndexVect(ss, subss));
	if (indexParts[indexParts.size() - 1].size() == 0) flag = false;

	return flag;
}*/

void *ThreadSearchIndexVect(void *threadarg)
{
 struct thread_data *my_data;
 my_data = (struct thread_data *) threadarg;
int numb = my_data->n;

	while (numb < parts.size())
	{
		string subss = parts[numb];
		string sss = my_data->s;
		vector<int> promV;
		if (subss.empty())
		{
			for (int i = 0; i < sss.size(); i++) promV.insert(promV.end(), i);
		}
		else
		{
			int k = 0;
			while (sss.find(subss) != -1)
			{
				promV.insert(promV.end(), sss.find(subss) + k);
				k = k + sss.find(subss) + 1;
				sss.erase(0, sss.find(subss) + 1);
			}
		}
		indexParts[numb] = promV;
		numb += 4;
	}
}
bool SearchElement(string ss, string subss)
{
	bool flag = true;
	while (subss.find("*") != -1)
	{
		parts.insert(parts.end(), subss.substr(0, subss.find("*")));
		lenLast = subss.substr(0, subss.find("*")).length();
		subss.erase(0, subss.find("*") + 1);
	}
	if (!subss.empty())	parts.insert(parts.end(), subss);
	vector <int> prom;
	for (int i = 0; i < parts.size(); i++) indexParts.insert(indexParts.end(), prom);

	pthread_t threads[4];
   	struct thread_data td[4];
	int rc;

	for(int i=0; i < 4; i++ )
	{
		td[i].n = i;
		td[i].s = ss;
 		rc = pthread_create(&threads[i], NULL, ThreadSearchIndexVect, (void *)&td[i]);
	}

	pthread_exit(NULL);

	for (int i = 0; i < indexParts.size(); i++)
	  if (indexParts[i].size() == 0) flag = false;
  return flag;
}

void FindMatchIndexes()
{
	vector<int> numbI, clock(indexParts.size(), 0), promSort, prom;
	for (int i = 0; i < indexParts.size(); i++) numbI.insert(numbI.end(), indexParts[i].size() - 1);
	while (clock[0] <= numbI[0])
	{
		for (int j = 0; j < clock.size(); j++) prom.insert(prom.end(), indexParts[j][clock[j]]);
		promSort = prom;
		sort(promSort.begin(), promSort.end());
		if (prom == promSort)
		{
			string pr = "Pos: " + to_string(prom[0]) + " " + s.substr(prom[0], prom[prom.size() - 1] - prom[0] + lenLast);
			res.insert(pair<string, bool>(pr, true));
		}
		prom.clear();

		clock[clock.size() - 1]++;
		for (int i = clock.size() - 1; i > 0; i--)
		if (clock[i] > numbI[i])
		{
			clock[i] = 0;
			clock[i - 1]++;
		}
	}
}

void DelSimEl()
{
	/*int i = 0;
	while (i < res.size() - 1)
	{
		int j = i + 1;
		while (j < res.size())
		if (res[i] == res[j]) res.erase(res.begin() + j);
		else j++;
		i++;
	}*/
		for (auto i = res.begin(); i != res.end(); i++) fout << i->first << "\n";
}

int main()
{
//	fout.open("res.txt", ios::out);


		for (int i = 0; i < 10; i++) s += s;
		if (SearchElement(s, subs))
		{
			if (!indexParts.empty())
			{
				res.clear();
				FindMatchIndexes();
				DelSimEl();
			}
//			else fout << "Any string \n"; // subs == "*"
		}
//		else fout << "No match \n";
//	fout.close();
	//system("pause");
	return 0;
}
