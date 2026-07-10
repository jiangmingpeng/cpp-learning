#define _CRT_SECURE_NO_WARNINGS
#include "RBTree.h"

void test()
{
	RBTree<string, string> rb;

	rb.Insert({ "insert","插入" });
	rb.Insert({ "int","整型" });
	rb.Insert({ "time","时间" });
	rb.Insert({ "string","字符串" });

	rb.InOrder();

	cout << endl;
	cout << rb.Find("inset")<< endl;
	cout<<rb.IsBalance();//检查是否符合 红黑树的规则
}

int main()
{
	test();

	return 0;
}