#define _CRT_SECURE_NO_WARNINGS
//-----------再探构造函数-------
//#include<iostream>
//using namespace std;
//class Time
//{
//public:
//	Time(int hour = 1)
//		:_hour(hour)
//	{
//		cout << "Time()" << endl;
//	}
//private:
//	int _hour;
//};
//class Date
//{
//public:
//	Date(int& x, int year = 1, int month = 1, int day = 1)
//		//:_year(year)
//		: _month(month)
//		, _day(day)
//		, _t()
//		,_ref(x)
//		,_n(30)
//		//1.类内初始值 =10 只是一个默认值，
//		//如果构造函数的初始化列表中没有显式初始化 _n，那么 _n 会被初始化为 10。
//		//2.如果初始化列表中写了 _n(30)，那么 _n 被初始化为 30，类内初始值被覆盖。
//		//3.const 的作用是：对象构造完成后，_n 的值不能再被改变。所以 其他成员函数中的赋值会编译报错
//	{
//		// error C2512: “Time”: 没有合适的默认构造函数可⽤
//		// error C2530 : “Date::_ref” : 必须初始化引⽤
//		// error C2789 : “Date::_n” : 必须初始化常量限定类型的对象
//	}
//	void Print() const
//	{
//		cout << _year << "-" << _month << "-" << _day << endl;
//	}
//private:
//	int _year= 10 ;//声明中的缺省参数
//	int _month;
//	int _day;
//	Time _t; // 没有默认构造
//	int& _ref; // 引⽤
//	const int _n=10; // const
//};
//int main()
//{
//	int i = 0;
//	Date d1(i);
//	d1.Print();
//	return 0;
//}

//#include<iostream>
//using namespace std;
//class A
//{
//public:
//	A(int a)
//		:_a1(a)//按照声明成员变量的顺序来初始化 变量
//		, _a2(_a1)//认真思考和体会下逻辑---再初始化列结束后发现没有声明的变量 则赋值缺省参数（声明中给的）
//	{}
//	void Print() {
//		cout << _a1 << " " << _a2 << endl;
//	}
//private:
//	int _a2 = 2;
//	int _a1 = 2;
//};
//int main()
//{
//	A aa(1);
//	aa.Print();
//}

//类型转化
//#include<iostream>
//using namespace std;
//class A
//{
//public:
//	 构造函数explicit就不再⽀持隐式类型转换
//	 explicit A(int a1)
//	A(int a1)
//		:_a1(a1)
//	{
//	}
//	explicit A(int a1, int a2)
//	A(int a1, int a2)
//		:_a1(a1)
//		, _a2(a2)
//	{
//	}
//	void Print()
//	{
//		cout << _a1 << " " << _a2 << endl;
//	}
//	int Get() const
//	{
//		return _a1 + _a2;
//	}
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//class B
//{
//public:
//	B(const A& a)
//		:_b(a.Get())
//	{
//	}
//private:
//	int _b = 0;
//};
//int main()
//{
//	 1构造⼀个A的临时对象，再⽤这个临时对象拷⻉构造aa3
//	 编译器遇到连续构造+拷⻉构造->优化为直接构造
//	A aa1 = 1;
//	aa1.Print();
//	const A& aa2 = 1;//这个可以理解为上面那条语句直接被优化掉的 中间步骤的显化
//	 C++11之后才⽀持多参数转化
//	A aa3 = { 2,2 };//这个道理一样只是参数变多了 用{}来传多个参数转化
//	 aa3隐式类型转换为b对象
//	 原理跟上⾯类似
//	B b = aa3;
//	const B& rb = aa3;
//	return 0;
//}

//-----static成员------
// 实现⼀个类，计算程序中创建出了多少个类对象？
//#include<iostream>
//using namespace std;
//class A
//{
//public:
//	A()
//	{
//		++_scount;
//	}
//	A(const A& t)
//	{
//		++_scount;
//	}
//	~A()
//	{
//		--_scount;
//	}//再该执行的程序执行结束后才执行析构函数 不能忘了
//	static int GetACount()
//	{
//		return _scount;
//	}
//private:
//	// 类⾥⾯声明
//	static int _scount;
//};
//// 类外⾯初始化
//int A::_scount = 0;
//int main()
//{
//	cout << A::GetACount() << endl;
//	//A a1, a2;
//	//A a3(a1);
//	A a1[10];
//	cout << A::GetACount() << endl;//可以用类名访问 也可以用对象访问
//	cout << a1[10].GetACount() << endl;
//	// 编译报错：error C2248: “A::_scount”: ⽆法访问 private 成员(在“A”类中声明)
//	//cout << A::_scount << endl;
//	return 0;
//}

//友元--函数友元--类友元
//#include<iostream>
//using namespace std;
//// 前置声明，都则A的友元函数声明编译器不认识B
//class B;//不同类中的成员函数可以 相互友元
//class A
//{
//	// 友元声明
//	friend void func(const A& aa, const B& bb);
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//class B
//{
//	// 友元声明
//	friend void func(const A& aa, const B& bb);
//private:
//	int _b1 = 3;
//	int _b2 = 4;
//};
//void func(const A& aa, const B& bb)
//{
//	cout << aa._a1 << endl;
//	cout << bb._b1 << endl;
//}
//int main()
//{
//	A aa;
//	B bb;
//	func(aa, bb);
//	return 0;
//}

//#include<iostream>
//using namespace std;
//class A
//{
//	//友元声明
//	friend class B;//在B中可以使用A的成员变量
//private:
//	int _a1 = 1;
//	int _a2 = 2;
//};
//class B
//{
//public:
//	void func1(const A& aa)
//	{
//		cout << aa._a1 << endl;
//		cout << _b1 << endl;
//	}
//	void func2(const A& aa)
//	{
//		cout << aa._a2 << endl;
//		cout << _b2 << endl;
//	}
//private:
//	int _b1 = 3;
//	int _b2 = 4;
//};
//int main()
//{
//	A aa;
//	B bb;
//	bb.func1(aa);
//	bb.func2(aa);
//	return 0;
//}

//------内部类-----

//#include<iostream>
//using namespace std;
//class A
//{
//private:
//	static int _k;
//	int _h = 1;
//public:
//	class B // B默认就是A的友元
//	{
//	public:
//		void foo(const A& a)
//		{
//			cout << _k << endl; //OK
//			cout << a._h << endl; //OK
//		}
//		int _b1;
//	};
//};
//int A::_k = 1;
//int main()
//{
//	cout << sizeof(A) << endl;//计算的依然是非静态成员变量 
//	A::B b;//如果B在外部的保护或者私立中则无法创建 属于非法访问
//	A aa;
//	b.foo(aa);
//	return 0;
//}
//匿名对象
#include<iostream>
using namespace std;
class A
{
public:
	A(int a = 0)
		:_a(a)
	{
		cout << "A(int a)" << endl;
	}
	~A()
	{
		cout << "~A()" << endl;
	}
private:
	int _a;
};
class Solution {
public:
	int Sum_Solution(int n) {
		//...
		return n;
	}
};
int main()
{
	A aa1;
	// 不能这么定义对象，因为编译器⽆法识别下⾯是⼀个函数声明，还是对象定义
	//A aa1();
	// 但是我们可以这么定义匿名对象，匿名对象的特点不⽤取名字，
	// 但是他的⽣命周期只有这⼀⾏，我们可以看到下⼀⾏他就会⾃动调⽤析构函数
	A();
	A(1);//即用即销毁
	A aa2(2);
	// 匿名对象在这样场景下就很好⽤，当然还有⼀些其他使⽤场景，这个我们以后遇到了再说
	Solution().Sum_Solution(10);//定义对象用的地方只有一处就推荐使用匿名对象--无论是调用函数 还是单纯使用对象
	return 0;
}