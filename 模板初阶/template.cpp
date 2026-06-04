#define _CRT_SECURE_NO_WARNINGS

//-----模版初阶----
//----泛型编程---
//void Swap(int& left, int& right)
//{
//	int temp = left;
//	left = right;
//	right = temp;
//}
//void Swap(double& left, double& right)
//{
//	double temp = left;
//	left = right;
//	right = temp;
//}
//void Swap(char& left, char& right)
//{
//	char temp = left;
//	left = right;
//	right = temp;
//}
//---模板-函数模板和类模板---
template <typename T>
//注意：typename是用来定义模板参数关键字，
//也可以使用class(切记：不能使用struct代替class)
void Swap(T& x, T& y)//T可以代表任意内置类型 编译器自动识别类型 然后调用相应的函数
{
	T temp = x;
	x = y;
	y = temp;
}
//---函数模板的隐式实例化---让编译器根据实参推演模板参数的实际类型
template <typename T>
T Add(const T& left,const T& right)
{
	return left + right + 10;
}
//int Add(const int left, const int right)
//{
//	return left + right;
//}
int main()
{
	int a = 10, b = 33;
	Swap(a, b);//---函数模板的隐式实例化
	double x = 10.2, y = 10.3;//如果类型不匹配，编译器会尝试进行隐式类型转换，如果无法转换成功编译器将会报错
	Add(a, (int)y);//若存在普通函数则会进入普通函数进行强制类型转化丢失精度值 无则需要自己强转所需类型
	Add<double>(x, b);//---函数模板的显式实例化
	return 0;
}

//函数匹配原则1. 一个非模板函数可以和一个同名的函数模板同时存在，而且该函数模板还可以被实例化为这个非模板函数
//函数匹配原则2.对于非模板函数和同名函数模板，如果其他条件都相同，在调动时会优先调用非模板函数而
//不会从该模板产生出一个实例。如果模板可以产生一个具有更好匹配的函数， 那么将选择模板
//函数匹配原则3. 模板函数不允许自动类型转换，但普通函数可以进行自动类型转换

//---类模板
//template<class T1, class T2,class Tn>
//class 类模板名
//{
//	// 类内成员定义
//};
#include<iostream>
using namespace std;
// 类模版
template<typename T>
class Stack
{
public:
	Stack(size_t capacity = 4)
	{
		_array = new T[capacity];
		_capacity = capacity;
		_size = 0;
	}
	void Push(const T& data);
private:
	T* _array;
	size_t _capacity;
	size_t _size;
};
// 模版不建议声明和定义分离到两个文件.h 和.cpp会出现链接错误
template<class T>
void Stack<T>::Push(const T& data)
{
	// 扩容
	_array[_size] = data;
	++_size;
}
int main()
{
	Stack<int> st1; // int-----就是用一段栈的代码得到实例化可以存储不同类型的栈空间栈对象
	Stack<double> st2; // double
	//类模板实例化与函数模板实例化不同，类模板实例化需要在类模板名字后跟<>，
	//然后将实例化的
	//类型放在<>中即可，类模板名字不是真正的类，而实例化的结果才是真正的类。

	return 0;
}



