#define _CRT_SECURE_NO_WARNINGS


#include "counter.h"

int main()
{
	size_t i = 0;
	vector<string> v;
	//string str = "1+2-3";
	string str = "1+2-(3*4+5)-7";
	Solution().toRPN(str, i, v);
	for (auto& e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	return 0;
}
