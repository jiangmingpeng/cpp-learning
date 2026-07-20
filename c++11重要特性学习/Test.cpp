#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <vector>
#include<iostream>

using namespace std;
struct Point
{
	int _x;
	int _y;
};
class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
		:_year(year)
		, _month(month)
		, _day(day)
	{
		cout << "Date(int year, int month, int day)" << endl;
	}
	Date(const Date& d)
		:_year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		cout << "Date(const Date& d)" << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
// ⼀切皆可⽤列表初始化，且可以不加=


//int main()
//{
//	//// C++98⽀持的
//	//int a1[] = { 1, 2, 3, 4, 5 };
//	//int a2[5] = { 0 };
//	//Point p = { 1, 2 };
//	//// C++11⽀持的
//	//// 内置类型⽀持
//	//int x1 = { 2 };
//	//// ⾃定义类型⽀持
//	//// 这⾥本质是⽤{ 2025, 1, 1}构造⼀个Date临时对象
//	//// 临时对象再去拷⻉构造d1，编译器优化后合⼆为⼀变成{ 2025, 1, 1}直接构造初始化d1
//	//	// 运⾏⼀下，我们可以验证上⾯的理论，发现是没调⽤拷⻉构造的
//	//Date d1 = { 2025, 1, 1 };
//	//// 这⾥d2引⽤的是{ 2024, 7, 25 }构造的临时对象
//	//const Date& d2 = { 2024, 7, 25 };
//	//// 需要注意的是C++98⽀持单参数时类型转换，也可以不⽤{}
//	//Date d3 = { 2025 };
//	//Date d4 = 2025;
//	//// 可以省略掉=
//	//Point p1{ 1, 2 };
//	//int x2{ 2 };
//	//Date d6{ 2024, 7, 25 };
//	//const Date& d7{ 2024, 7, 25 };
//	//// 不⽀持，只有{}初始化，才能省略=
//	//// Date d8 2025;
//	//vector<Date> v;
//	//v.push_back(d1);
//	//v.push_back(Date(2025, 1, 1));//匿名对象传参
//	//// ⽐起有名对象和匿名对象传参，这⾥{}更有性价⽐
//	//v.push_back({ 2025, 1, 1 });
//
//
//	// 左值：可以取地址
//// 以下的p、b、c、*p、s、s[0]就是常⻅的左值
//	int* p = new int(0);
//	int b = 1;
//	const int c = b;
//	*p = 10;
//	string s("111111");
//	s[0] = 'x';
//	cout << &c << endl;
//	cout << (void*)&s[0] << endl;//这里强转void* 
//	// 右值：不能取地址
//	double x = 1.1, y = 2.2;
//	// 以下⼏个10、x + y、fmin(x, y)、string("11111")都是常⻅的右值
//	10;
//	x + y;
//	fmin(x, y);
//	//string("11111");
//	//cout << &10 << endl;
//	//cout << &(x+y) << endl;
//	//cout << &(fmin(x, y)) << endl;
//	//cout << &string("11111") << endl;
//	return 0;
//}


//int main()
//{
//	std::string s1 = "Test";//右值引用不能绑定左值
//	// std::string&& r1 = s1; // 错误：不能绑定到左值
//	const std::string& r2 = s1 + s1; // OK：到 const 的左值引⽤延⻓⽣存期（这里的s1+s1是常量）
//	// r2 += "Test"; // 错误：不能通过到 const 的引⽤修改
//	std::string&& r3 = s1 + s1; // OK：右值引⽤延⻓⽣存期
//	r3 += "Test"; // OK：能通过到⾮ const 的引⽤修改
//	std::cout << r3 << '\n';
//	return 0;
//}

//void f(int& x)
//{
//	std::cout << "左值引⽤重载 f(" << x << ")\n";
//}
//void f(const int& x)
//{
//	std::cout << "到 const 的左值引⽤重载 f(" << x << ")\n";
//}
//void f(int&& x)
//{
//	std::cout << "右值引⽤重载 f(" << x << ")\n";
//}
//int main()
//{
//	int i = 1;
//	const int ci = 2;
//	f(i); // 调⽤ f(int&)
//	f(ci); // 调⽤ f(const int&)
//	f(3); // 调⽤ f(int&&)，如果没有 f(int&&) 重载则会调⽤ f(const int&)
//	f(std::move(i)); // 调⽤ f(int&&)
//	// 右值引⽤变量在⽤于表达式时是左值
//	int&& x = 1;//右值引用后的x具有左值属性
//	f(x); // 调⽤ f(int& x)
//	f(std::move(x)); // 调⽤ f(int&& x)
//	return 0;
//}


//
//class Solution {
//public:
//	 传值返回需要拷⻉
//	string addStrings(string num1, string num2) {
//		string str;
//		int end1 = num1.size() - 1, end2 = num2.size() - 1;
//		 进位
//		int next = 0;
//		while (end1 >= 0 || end2 >= 0)
//		{
//			int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
//			int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
//			int ret = val1 + val2 + next;
//			next = ret / 10;
//			ret = ret % 10;
//			str += ('0' + ret);
//		}
//		if (next == 1)
//			str += '1';
//		reverse(str.begin(), str.end());
//		return str;
//	}
//};
//class Solution {
//public:
//	// 这⾥的传值返回拷⻉代价就太⼤了
//	vector<vector<int>> generate(int numRows) {
//		vector<vector<int>> vv(numRows);
//		for (int i = 0; i < numRows; ++i)
//		{
//			vv[i].resize(i + 1, 1);
//		}
//		for (int i = 2; i < numRows; ++i)
//		{
//			for (int j = 1; j < i; ++j)
//			{
//				vv[i][j] = vv[i - 1][j] + vv[i - 1][j - 1];
//			}
//		}
//		return vv;
//	}
//};



#include<iostream>
#include<assert.h>
#include<string.h>
#include<algorithm>
using namespace std;
namespace jmp
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		string(const char* str = "")
			:_size(strlen(str))
			, _capacity(_size)
		{
			cout << "string(char* str)-构造" << endl;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}
		void swap(string& s)
		{
			::swap(_str, s._str);
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
		string(const string& s)
			:_str(nullptr)
		{
			cout << "string(const string& s) -- 拷贝构造" << endl;

			reserve(s._capacity);
			for (auto ch : s)
			{
				push_back(ch);
			}
		}
		// 移动构造
		string(string&& s)
		{
			cout << "string(string&& s) -- 移动构造" << endl;
			swap(s);
		}
		string& operator=(const string& s)
		{
			cout << "string& operator=(const string& s) -- 拷贝赋值" << endl;
			if (this != &s)
			{
				_str[0] = '\0';
				_size = 0;
				reserve(s._capacity);
				for (auto ch : s)
				{
					push_back(ch);
				}
			}
			return *this;
		}
		// 移动赋值
		string& operator=(string&& s)
		{
			cout << "string& operator=(string&& s) -- 移动赋值" << endl;
			swap(s);
			return *this;
		}
		~string()
		{
			cout << "~string() -- 析构" << endl;
			delete[] _str;
			_str = nullptr;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* tmp = new char[n + 1];
				if (_str)
				{
					strcpy(tmp, _str);
					delete[] _str;
				}
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char ch)
		{
			if (_size >= _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity *
					2;
				reserve(newcapacity);
			}
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		const char* c_str() const
		{
			return _str;
		}

		size_t size() const
		{
			return _size;
		}

	private:
		char* _str = nullptr;
		size_t _size = 0;
		size_t _capacity = 0;
	};
	string addStrings(string num1, string num2)
	{
		string str;
		int end1 = num1.size() - 1, end2 = num2.size() - 1;
		int next = 0;
		while (end1 >= 0 || end2 >= 0)
		{
			int val1 = end1 >= 0 ? num1[end1--] - '0' : 0;
			int val2 = end2 >= 0 ? num2[end2--] - '0' : 0;
			int ret = val1 + val2 + next;
			next = ret / 10;
			ret = ret % 10;
			str += ('0' + ret);
		}

		if (next == 1)
			str += '1';
		reverse(str.begin(), str.end());
		cout << "******************************" << endl;
		return str;
	}

}
//int main()
//{
//	//jmp::string s1("xxxxx");
//	//// 拷⻉构造
//	//jmp::string s2 = s1;
//	//// 构造+移动构造，优化后直接构造
//	//jmp::string s3 = jmp::string("yyyyy");
//	//// 移动构造
//	//jmp::string s4 = move(s1);
//	//cout << "******************************" << endl;
//	//jmp::string ret = jmp::addStrings("11111", "2222");
//	//cout << ret.c_str() << endl;
//
//	jmp::string ret;
//	ret = jmp::addStrings("11111", "2222");//里面的参数 先构造两个临时对象 add又构造一个临时对象 同时前面两个析构掉 后面这个临时对象又移动赋值给ret
//	cout << ret.c_str() << endl;
//	return 0;
//}


#include "list.h"
#include <list>
//int main()
//{
//	bit::list<jmp::string> lt;
//	jmp::string s1("111111111111111111111");
//	lt.push_back(s1);
//	cout << "*************************" << endl;
//	lt.push_back(jmp::string("22222222222222222222222222222"));
//	cout << "*************************" << endl;
//	lt.push_back("3333333333333333333333333333");
//	cout << "*************************" << endl;
//	lt.push_back(move(s1));
//	cout << "*************************" << endl;
//	return 0;
//}




//// 由于引⽤折叠限定，f1实例化以后总是⼀个左值引⽤
//template<class T>
//void f1(T& x)
//{
//}
//// 由于引⽤折叠限定，f2实例化后可以是左值引⽤，也可以是右值引⽤
//template<class T>
//void f2(T&& x)
//{
//}
//int main()
//{
//	typedef int& lref;
//	typedef int&& rref;
//	int n = 0;
//	lref& r1 = n; // r1 的类型是 int&
//	lref&& r2 = n; // r2 的类型是 int&
//	rref& r3 = n; // r3 的类型是 int&
//	rref&& r4 = 1; // r4 的类型是 int&&
//	// 没有折叠->实例化为void f1(int& x)
//	f1<int>(n);
//	//f1<int>(0); // 报错
//	// 折叠->实例化为void f1(int& x)
//	f1<int&>(n);
//	//f1<int&>(0); // 报错
//	// 折叠->实例化为void f1(int& x)
//	f1<int&&>(n);
//	//f1<int&&>(0); // 报错
//	// 折叠->实例化为void f1(const int& x)
//	f1<const int&>(n);
//	f1<const int&>(0);
//	// 折叠->实例化为void f1(const int& x)
//	f1<const int&&>(n);
//	f1<const int&&>(0);
//	// 没有折叠->实例化为void f2(int&& x)
//	//f2<int>(n); // 报错
//	f2<int>(0);
//	// 折叠->实例化为void f2(int& x)
//	f2<int&>(n);
//	//f2<int&>(0); // 报错
//	// 折叠->实例化为void f2(int&& x)
//	//f2<int&&>(n); // 报错
//	f2<int&&>(0);
//	return 0;
//}


//template<class T>
//void Function(T&& t)
//{
//	int a = 0;
//	T x = a;
//	x++;
//	cout << &a << endl;
//	cout << &x << endl << endl;
//}
//int main()
//{
//	// 10是右值，推导出T为int，模板实例化为void Function(int&& t)
//	//Function(10); // 右值
//	int a;
//	// a是左值，推导出T为int&，引⽤折叠，模板实例化为void Function(int& t)
//	Function(a); // 左值
//	// std::move(a)是右值，推导出T为int，模板实例化为void Function(int&& t)
//	Function(std::move(a)); // 右值
//	const int b = 8;
//	// a是左值，推导出T为const int&，引⽤折叠，模板实例化为void Function(const int&t)
//	// 所以Function内部会编译报错，x不能++
//	Function(b); // const 左值----x不能++
//	// std::move(b)右值，推导出T为const int，模板实例化为void Function(const int&&t)
//	// 所以Function内部会编译报错，x不能++
//	Function(std::move(b)); // const 右值
//	return 0;
//}



//void Fun(int& x) { cout << "左值引用" << endl; }
//void Fun(const int& x) { cout << "左值引用" << endl; }
//void Fun(int&& x) { cout << "右值引用" << endl; }
//void Fun(const int&& x) { cout << "const 右值引用" << endl; }
//template<class T>
//void Function(T&& t)
//{
//	//Fun(t);
//	Fun(forward<T>(t));//完美转发 保留左右值属性往下传
//}
//int main()
//{
//	// 10是右值，推导出T为int，模板实例化为void Function(int&& t)
//	Function(10); // 右值
//	int a;
//	// a是左值，推导出T为int&，引⽤折叠，模板实例化为void Function(int& t)
//	Function(a); // 左值
//	// std::move(a)是右值，推导出T为int，模板实例化为void Function(int&& t)
//	Function(std::move(a)); // 右值
//	const int b = 8;
//	// a是左值，推导出T为const int&，引⽤折叠，模板实例化为void Function(const int&t)
//	Function(b); // const 左值
//	// std::move(b)右值，推导出T为const int，模板实例化为void Function(const int&&t)
//	Function(std::move(b)); // const 右值
//	return 0;
//}


//template <class ...Args>
//void Print(Args&&... args)
//{
//	cout << sizeof...(args) << endl;//sizeof...()专门用来计算参数包的参数个数
//}
//int main()
//{
//	double x = 2.2;
//	Print(); // 包⾥有0个参数
//	Print(1); // 包⾥有1个参数
//	Print(1, string("xxxxx")); // 包⾥有2个参数
//	Print(1.1, string("xxxxx"), x); // 包⾥有3个参数
//	return 0;
//}

// 可变模板参数
// 参数类型可变
// 参数个数可变
// 打印参数包内容
//template <class ...Args>
//void Print(Args... args)
//{
// // 可变参数模板编译时解析
// // 下⾯是运⾏获取和解析，所以不⽀持这样⽤
// cout << sizeof...(args) << endl;
// for (size_t i = 0; i < sizeof...(args); i++)
// {
// cout << args[i] << " ";
// }
// cout << endl;
//}


//
//void ShowList()
//{
//	// 编译器时递归的终⽌条件，参数包是0个时，直接匹配这个函数
//	cout << endl;
//}
//template <class T, class ...Args>
//void ShowList(T x, Args... args)
//{
//	cout << x << " ";
//	// args是N个参数的参数包
//	// 调⽤ShowList，参数包的第⼀个传给x，剩下N-1传给第⼆个参数包
//	ShowList(args...);
//}
//// 编译时递归推导解析参数
//template <class ...Args>
//void Print(Args... args)
//{
//	ShowList(args...);
//}
//int main()
//{
//	Print();
//	Print(1);
//	Print(1, string("xxxxx"));
//	Print(1, string("xxxxx"), 2.2);
//	return 0;
//}


//
//template <class T>
//const T& GetArg(const T& x)
//{
//	cout << x << " ";
//	return x;
//}
//template <class ...Args>
//void Arguments(Args... args)
//{
//}
//template <class ...Args>
//void Print(Args... args)
//{
//	// 注意GetArg必须返回或者到的对象，这样才能组成参数包给Arguments
//	Arguments(GetArg(args)...);//把参数包一一解析出来
//}
//// 本质可以理解为编译器编译时，包的扩展模式
//// 将上⾯的函数模板扩展实例化为下⾯的函数
//
////void Print(int x, string y, double z)
////{
//// Arguments(GetArg(x), GetArg(y), GetArg(z));
////}
//int main()
//{
//	Print(1, string("xxxxx"), 2.2);
//	return 0;
//}


//#include<list>
//// emplace_back总体⽽⾔是更⾼效，推荐以后使⽤emplace系列替代insert和push系列
//int main()
//{
//	list<jmp::string> lt;
//	// 传左值，跟push_back⼀样，⾛拷⻉构造
//	jmp::string s1("111111111111");
//	lt.emplace_back(s1);
//	cout << "*********************************" << endl;
//	// 右值，跟push_back⼀样，⾛移动构造
//	lt.emplace_back(move(s1));
//	cout << "*********************************" << endl;
//	// 直接把构造string参数包往下传，直接⽤string参数包构造string
//	// 这⾥达到的效果是push_back做不到的
//	lt.emplace_back("111111111111");
//	cout << "*********************************" << endl;
//	list<pair<jmp::string, int>> lt1;
//	// 跟push_back⼀样
//	// 构造pair + 拷⻉/移动构造pair到list的节点中data上
//	pair<jmp::string, int> kv("苹果", 1);
//	lt1.emplace_back(kv);
//	cout << "*********************************" << endl;
//	// 跟push_back⼀样
//	lt1.emplace_back(move(kv));
//	cout << "*********************************" << endl;
//	////////////////////////////////////////////////////////////////////
//	// 直接把构造pair参数包往下传，直接⽤pair参数包构造pair
//	// 这⾥达到的效果是push_back做不到的
//	lt1.emplace_back("苹果", 1);
//	cout << "*********************************" << endl;
//	return 0;
//}


//#include"list.h"
// emplace_back总体⽽⾔是更⾼效，推荐以后使⽤emplace系列替代insert和push系列
//int main()
//{
//	bit::list<jmp::string> lt;
//	// 传左值，跟push_back⼀样，⾛拷⻉构造
//	jmp::string s1("111111111111");
//	lt.emplace_back(s1);
//	cout << "*********************************" << endl;
//	// 右值，跟push_back⼀样，⾛移动构造
//	lt.emplace_back(move(s1));
//	cout << "*********************************" << endl;
//	// 直接把构造string参数包往下传，直接⽤string参数包构造string
//	// 这⾥达到的效果是push_back做不到的
//	lt.emplace_back("111111111111");
//	cout << "*********************************" << endl;
//	bit::list<pair<jmp::string, int>> lt1;
//	// 跟push_back⼀样
//	// 构造pair + 拷⻉/移动构造pair到list的节点中data上
//	pair<jmp::string, int> kv("苹果", 1);
//	lt1.emplace_back(kv);
//	cout << "*********************************" << endl;
//	// 跟push_back⼀样
//	lt1.emplace_back(move(kv));
//	cout << "*********************************" << endl;
//	////////////////////////////////////////////////////////////////////
//	// 直接把构造pair参数包往下传，直接⽤pair参数包构造pair
//	// 这⾥达到的效果是push_back做不到的
//	lt1.emplace_back("苹果", 1);
//	cout << "*********************************" << endl;
//		return 0;
//}


//class Person
//{
//public:
//	Person(const char* name = "", int age = 0)
//		:_name(name)
//		, _age(age)
//	{
//	}
//	Person(const Person& p)
//		:_name(p._name)
//		, _age(p._age)
//	{}
//	Person(Person&& p) = default;
//	//Person(const Person& p) = delete;
//private:
//	jmp::string _name;
//	int _age;
//};
//int main()
//{
//	Person s1;
//	Person s2 = s1;
//	Person s3 = std::move(s1);
//	return 0;
//}
//
//
//int main()
//{
//	// ⼀个简单的lambda表达式-----本质上还是 调用operator()像个仿函数一样的
//	auto add1 = [](int x, int y)->int {return x + y; };
//	auto add2 = [](float x, float y)->double {return x - y; };//注意分号是语句的的分号 如果在某个参数位置 使用lambda }后面不要加} 
//	cout << add1(1, 2) << endl;
//	// 1、捕捉为空也不能省略
//	// 2、参数为空可以省略
//	// 3、返回值可以省略，可以通过返回对象⾃动推导
//	// 4、函数题不能省略
//	auto func1 = []
//		{
//			cout << "hello bit" << endl;
//			return 0;
//		};
//	func1();
//	int a = 0, b = 1;
//	auto swap1 = [](int& x, int& y)
//		{
//			int tmp = x;
//			x = y;
//			y = tmp;
//		};
//	swap1(a, b);
//	cout << a << ":" << b << endl;
//	return 0;
//}


//int x = 0;
//// 捕捉列表必须为空，因为全局变量不⽤捕捉就可以⽤，没有可被捕捉的变量
//auto func1 = []()
//	{
//		x++;
//	};
//int main()
//{
//	// 只能⽤当前lambda局部域和捕捉的对象和全局对象
//	int a = 0, b = 1, c = 2, d = 3;
//	auto func1 = [a, &b]//注意这里的&是引用不是取地址 不能搞混了
//		{
//			// 值捕捉的变量不能修改，引⽤捕捉的变量可以修改
//			//a++;
//			b++;
//			int ret = a + b;
//			return ret;
//		};
//	cout << func1() << endl;
//	// 隐式值捕捉
//	// ⽤了哪些变量就捕捉哪些变量
//	auto func2 = [=]
//		{
//			int ret = a + b + c;
//			return ret;
//		};
//	cout << func2() << endl;
//	// 隐式引⽤捕捉
//	// ⽤了哪些变量就捕捉哪些变量
//	auto func3 = [&]
//		{
//			a++;
//			c++;
//			d++;
//		};
//	func3();
//	cout << a << " " << b << " " << c << " " << d << endl;
//	// 混合捕捉1
//	auto func4 = [&, a, b]
//		{
//			//a++;
//			//b++;
//			c++;
//			d++;
//			return a + b + c + d;
//		};
//	func4();
//	cout << a << " " << b << " " << c << " " << d << endl;
//	// 混合捕捉1
//	auto func5 = [=, &a, &b]
//		{
//			a++;
//			b++;
//			/*c++;
//			d++;*/
//			return a + b + c + d;
//		};
//	func5();
//	cout << a << " " << b << " " << c << " " << d << endl;
//	// 局部的静态和全局变量不能捕捉，也不需要捕捉
//	static int m = 0;
//	auto func6 = []
//		{
//			int ret = x + m;
//			return ret;
//		};
//	// 传值捕捉本质是⼀种拷⻉,并且被const修饰了
//	// mutable相当于去掉const属性，可以修改了
//	// 但是修改了不会影响外⾯被捕捉的值，因为是⼀种拷⻉
//	auto func7 = [=]()mutable
//		{
//			a++;
//			b++;
//			c++;
//			d++;
//			return a + b + c + d;
//		};
//	cout << func7() << endl;
//	cout << a << " " << b << " " << c << " " << d << endl;
//	return 0;
//}
//
//
//class Rate
//{
//public:
//	Rate(double rate)
//		: _rate(rate)
//	{
//	}
//	double operator()(double money, int year)
//	{
//		return money * _rate * year;
//	}
//private:
//	double _rate;
//};
//int main()
//{
//	double rate = 0.49;
//	// lambda
//	auto r2 = [rate](double money, int year) 
//	{
//		return money * rate * year;
//	};
//	// 函数对象
//	Rate r1(rate);
//	r1(10000, 2);//仿函数的调用
//	r2(10000, 2);//lambda 表达式的调用
//	auto func1 = [] 
//	{
//		cout << "hello world" << endl;
//	};
//	func1();
//	return 0;
//}
//
//
//#include <functional>
//using namespace std;
//
//// 1. 普通函数
//int add(int a, int b) { return a + b; }
//
//// 2. 仿函数（重载了 operator() 的类）
//struct Mul {
//	int operator()(int a, int b) { return a * b; }
//};
//
//int main() {
//	// 定义一个插座（接收两个 int，返回 int）
//	function<int(int, int)> func;
//
//	// 插上普通函数
//	func = add;
//	cout << func(3, 4) << endl; // 输出 7
//
//	// 插上仿函数
//	func = Mul();
//	cout << func(3, 4) << endl; // 输出 12
//
//	// 插上 Lambda
//	func = [](int a, int b) { return a - b; };
//	cout << func(3, 4) << endl; // 输出 -1
//}



//#include <functional>//function 和 bind都在这个头文件中
//using namespace std;
//
//// 一个需要 3 个参数的函数
//void print_sum(int a, int b, int c) 
//{
//	cout << a + b + c << endl;
//}
//
//int main() {
//	// 1. 提前把第一个参数 a 固定为 10，后面的 b 和 c 保留（用占位符 _1, _2）
//	// 注意：占位符存在 std::placeholders 命名空间里
//	using namespace std::placeholders;//bind的占位符
//	auto new_func = bind(print_sum, 10, _1, _2);//可以改变参数的顺序 参数的数量 数量一般是 通过确定某个参数的值 来控制参数的数量
//
//	// 现在 new_func 就变成了只需要传 2 个参数的新函数
//	new_func(20, 30); // 等价于 print_sum(10, 20, 30)，输出 60
//
//	// 2. 你也可以调整参数顺序（把第三个参数移到第一个来）
//	auto reversed_func = bind(print_sum, _3, _2, _1);
//	reversed_func(100, 200, 300); // 等价于 print_sum(300, 200, 100)，输出 600
//	return 0;
//}

#include <functional>//function 和 bind都在这个头文件中
using namespace std;
void process_data(string machine_name, int data_id) 
{
	cout << machine_name << " 处理了数据: " << data_id << endl;
}

int main() {
	// 你有一堆数据 ID，但机器名字早就定好了
	using namespace std::placeholders;
	function<void(int)> process_on_main = bind(process_data, "MainServer", _1);

	// 模拟来了 5 个任务
	process_on_main(101);
	process_on_main(102);
}
// 输出：
// MainServer 处理了数据: 101
// MainServer 处理了数据: 102