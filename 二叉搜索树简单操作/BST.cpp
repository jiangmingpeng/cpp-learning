#define _CRT_SECURE_NO_WARNINGS


#include "BST.h"

int main()
{
	BSTree<int> vt;
	int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	for (auto e : a)
	{
		vt.Insert(e);
	}
	cout << vt.Find(55) << endl;//查找逻辑没什么问题
	vt.Inoder();
	cout << vt.Erase(8) << endl;
	vt.Inoder();

	//cout << vt.Erase(10) << endl;
	//vt.Inoder();
	//cout << vt.Erase(3) << endl;
	//vt.Inoder();

	//cout << vt.Erase(1) << endl;//查找逻辑没什么问题

	return 0;

}