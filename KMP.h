#ifndef _KMP_
#define _KMP_
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int* getNext(string ps)
{
	const char* p = ps.c_str();
	int* next = new int[ps.length()];
	next[0] = -1;
	int j = 0;
	int k = -1;
	while (j < ps.length()-1)
	{
		if (k == -1||ps[j]==ps[k])
		{
			j++;
			k++;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
	return next;
}

int KMP(string ts,string ps)
{
	const char* c_ts = ts.c_str();
	const char* c_ps = ps.c_str();
	int i = 0;//主串的位置
	int j = 0;//模板串的位置
	int* next = getNext(ps);//获取next数组
	int ts_length = ts.length();
	int ps_length = ps.length();
	while (i < ts_length&&j < ps_length)
	{
		char ct = *(c_ts + i);
		char cp = *(c_ps + j);
		if (ct == cp)
		{
			i++;
			j++;
		}
		else if (ct != cp && j != -1)
		{
			//i不需要回溯
			j = next[j];
		}
		else if (ct!=cp&&j == -1)
		{
			//i回溯
			j++; //j回到指定位置
			i++;
		}
	}

	if (j == ps.length())
	{
		return i - j;
	}
	else
	{
		return -1;
	}
}

#endif // !_KMP_

