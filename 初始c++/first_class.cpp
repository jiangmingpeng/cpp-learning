#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<assert.h>
//namespace本质是定义出⼀个域，
//这个域跟全局域各⾃独⽴，不同的域可以定义同名变量
//明白有 （全局域 局部域）--影响作用域和生命周期（命名空间域 类域）--不影响作用域和生命周期
//命名空间--从“std”库中全开查找 也可以单独开或者部分开 
//如写using std::cout/std::cin/std::endl等此类操作
//namespace test
//{
//	char bin[10] = "test";
	//int malloc = 999;//malloc 本身是一个开辟空间的函数 
	//但是在这里可以被定义变量是namespace的功劳 变相允许了重命名的操作
//}
//using namespace std;
//using std::endl;   using将命名空间中某个成员展开
//using std::cout;
//int main()
//{
//	//printf("%d\n", test::malloc);
//	//使⽤C++输⼊输出更⽅便，不需要像printf/scanf输⼊输出时那样，需要⼿动指定格式，
//	//C++的输⼊输出可以⾃动识别变量类型
//	cout << "我不是" << "\n" << "人机" << endl;
//	cin >> test::malloc>>test::bin;//<<是流插⼊运算符-输出操作，>>是流提取运算符输入操作。
//	cout << test::malloc << endl;
//	cout << test::bin << endl;
//	return 0;
//}
//int main()
//{
//	cout << "halle word!!"<<endl;
//	return 0;
//}
//using namespace std;
//缺省函数 
//int Add(int a = 20, int b = 10)
//{
//	return a + b;
//}
//int main()
//{
//	int a;
//	int b;
//	cin >> a >> b ;
//	int ret = Add();
//	//int ret = Add(a);
//	//int ret = Add(a,b);
//}
//函数重载---简单来说就是允许使用相同函数名 但是要保证参数类型,个数,位置的区别
//返回值不同不能作为重载条件,因为调⽤时也⽆法区分
//这样C++函数调⽤就表现出了多态⾏为
//void Swap(int* x, int* y)
//{
//	int temp = *x;
//	*x = *y;
//	*y = temp;
//}
//void Swap(char* x, char* y)
//{
//	char temp = *x;
//	*x = *y;
//	*y = temp;
//}

//int main()
//{
//	int a = 10;
//	int b = 90;
//	char c = 'S';
//	char d = 'B';
//	Swap(&a, &b);
//	Swap(&c, &d);
//}
// 下⾯两个函数构成重载
// f()但是调⽤时，会报错，存在歧义，编译器不知道调⽤谁
//void f1()
//{
//	cout << "f()" << endl;
//}
//void f1(int a = 10)//--缺省函数这样情况 调⽤时，会报错，存在歧义，编译器不知道调⽤谁 应该避免出现这种情况
//{
//	cout << "f(int a)" << endl;
//}

//引用---给变量取别名
//引⽤不是新定义⼀个变量，⽽是给已存在变量取了⼀个别名，编译器不会为引⽤变量开辟内存空间，
//它和它引⽤的变量共⽤同⼀块内存空间
//using namespace std;
//int main()
//{
//	int a = 999;
//	int& b = a;
//	int& c = b;
//	int x = 89446;
//	c = x;//可以通过别名对原来的元素进行赋值修改
//	cout << "a="<<a << "\n"<< "b=" << b <<"\n" << "c=" << c << endl;
//	cout << "a="<<&a << "\n"<< "b=" << &b <<"\n" << "c=" << &c << endl;
//	cout << c<<"\n"<<&c << endl;
//}

//引用的特性
/*typedef struct Stack
{
	int* arr;
	int size;
	int capacity;
}ST,*Stack;

Stack sta*/;//效果一样要明白什么意思
//ST* sta;
//用 ST*& 作为参数，可以在函数内修改外部指针本身。
//函数内直接对参数赋值，不要重新定义同名的局部变量，否则会遮蔽形参，导致外部指针不变。
//分配内存后还要正确初始化结构体成员（比如 sta->size = 0; 和 sta->arr 等）
//void InitStack(ST*& sta)
//{
//	sta = (ST*)malloc(sizeof(ST));
//	//...
//}
//void PushStack(ST*& st1, int x=0)
//{
//	//.....
//	(*st1).arr[(*st1).size++] = x;
//}
//void Swap(int& rx, const int& ry)
//{
//	//int temp = rx;
//	//rx = ry;
//	//ry = temp;
//}
//int& fun()//&int/int--把返回创建的一个临时变量给取了一个别名 否则只是把临时变量拷贝过去了
//{
//	int ret = 0;
//	//...
//	return ret;
//}
//int main()
//{
//	//InitStack(sta);
//	//PushStack(sta);
//	//int aad = ++fun();
//	//int aad = fun();
//	//int aav = 98;
//	int cca = 66;
//	int app = 9542;
//	Swap(cca, app);
//	//int& ppa;//“ppa”: 必须初始化引用
//	int& ppa = app;
//	cout << ppa << endl;
//
//	double test = 12.5;
//	int testb = test;
//	//int& testa = test;--------------------放大了&的特权所以是错误的
//	//const 引用可以绑定到右值和可隐式转换的类型，而非 const 引用不能
//	const int& testa = test;
//	Swap(app, testa);//对于引用值传参 在设置参数的时候就要注意 等级大小
//	cout << "testb = " << testb << " testa = " << testa << endl;

/*	int testc = 621;
	int& testca = testc;
	const int& testca = testc;*///平级转化和降级转换是允许的
	//const int testd = 689;
	////int& testda = testd;//升级转化是不允许的
	//const int& testda = testd;
//	return 0;
//}

//inline void Swap(int& rx, int& ry)//inline 原地展开函数执行 不创建函数栈帧 //适用于小函数且平凡调用的函数
//{
//	int temp = rx;
//	rx = ry;
//	ry = temp;
//}
//
//int main()
//{
//	int a = 999;
//	int b = 666;
//	Swap(a,b);
//	cout << "a = " << a << " b = " << b << endl;
//}

