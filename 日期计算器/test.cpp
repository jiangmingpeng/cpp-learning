#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
void test1()
{
	Date d1(2026, 4, 30);
	cout << "------加减测试---------" << endl;
	Date d3(d1 + 1000);
	d1.DatePrint();
	d3.DatePrint();
	cout << "---------------------" << endl;
	Date d4(d3 - 1000);
	d3.DatePrint();
	d4.DatePrint();
}
void test2()
{
	Date d1(2026, 4, 30);
	cout << "-----前置后置++--测试----" << endl;
	Date d5(d1);
	++d5;
	//d5.operator++();
	d5.DatePrint();
	cout << "---------------------" << endl;
	Date d6(d1);
	//d6++;//这里调用后置++ 压根没有存储他的放回值 仅仅是改变了旧值 并且形式上保存了旧值
	Date old1 = d6++;//在这里就保存了 后置++的放回值并且也修改成了值  如果要用就直接使用old对象
	old1.DatePrint();
	d6.DatePrint();
	cout << "---------------------" << endl;
	Date d7(d1);
	--d7;
	d7.DatePrint();
	cout << "---------------------" << endl;
	Date d8(d1);
	Date old2 = d8--;
	old2.DatePrint();
	d8.DatePrint();
} 
void test3()
{
	Date d1(2026, 4, 30);
	cout << "-----日期比较大小测试----" << endl;
	Date d9(3000, 6, 30);
	int ret1 = (d9 == d1);
	int ret2 = (d9 != d1);
	cout << ret1 << " " << ret2 << endl;
	cout << "---------------------" << endl;
	int ret3 = (d9 < d1);
	int ret4 = (d9 <= d1);
	cout << ret3 << " " << ret4 << endl;
	cout << "---------------------" << endl;
	int ret5 = (d9 > d1);
	int ret6 = (d9 >= d1);
	cout << ret5 << " " << ret6 << endl;
}
void test4()
{
	Date d1(2026, 4, 30);
	Date d10(3000, 6, 30);
	cout << "------日期差值测试------" << endl;
	int ret7 = (d10 - d1);
	cout << ret7 << endl;
	cout << "---------------------" << endl;
}
void test5()
{
	cout << "----对象的输入输出测试---"<<endl;
	Date d1(2026, 5, 1);
	Date d11;
	cin >> d11>>d1;
	cout << d11-d1 << endl;
}

int main()
{
	test5();
	
	
	return 0;
}
