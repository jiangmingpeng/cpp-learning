#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<vector>
#include <algorithm>
#include "template.h"

namespace JMP
{
	// 定义一个模板类型的静态数组
	template<class T, size_t N = 10>//非类型模板参数
	class array
	{
	public:
		T& operator[](size_t index) { return _array[index]; }
		const T& operator[](size_t index)const { return _array[index]; }
		size_t size()const { return _size; }
		bool empty()const { return 0 == _size; }
	private:
		T _array[N];//静态数组的创建 目的是可以同时创建不同大小的同一个 数组类型
		size_t _size;
	};
}

// 函数模板 -- 参数匹配
template<class T>
bool Less(T left, T right)
{
	return left < right;
}
//template<>//函数模板特化
//bool Less<Date*>(Date* left, Date* right)
//{
//	return *left < *right;
//}
bool Less(Date* left, Date* right)//一般对于函数模板来说如果出现需要特殊处理的  采用重载
//对于函数模板的特殊处理，使用重载（提供普通函数或另一个模板）
//通常比使用函数模板特化更安全、更符合重载解析规则，
//但效率上两者没有本质差别（都是编译期决议，最终生成的代码相同）
// 
//特化参与重载决议时行为容易出人意料：特化不会影响重载集的选择，
//只有基本模板才会被考虑，可能导致调用不是你想要的特化版本。
//重载更自然：提供普通函数或不同参数的模板，编译器能正确选择最匹配的版本。
{
	return *left < *right;
}


//int main()
//{
//	cout << Less(1, 2) << endl; // 可以比较，结果正确
//	Date d1(2022, 10, 7);
//	Date d2(2022, 7, 8);
//	cout << Less(d1, d2) << endl; // 可以比较，结果正确
//	Date* p1 = &d1;
//	Date* p2 = &d2;
//	cout << Less(p1, p2) << endl; // 可以比较，结果错误
//	return 0;
//}
//


template<class T1, class T2>
class Data
{
public:
	Data() { cout << "Data<T1, T2>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};

template<>//全特化
class Data<int, char>
{
public:
	Data() { cout << "Data<int, char>" << endl; }
private:
	int _d1;
	char _d2;
};

template<class T>//偏特化
class Data<T, char>
{
public:
	Data() { cout << "Data<T, char>" << endl; }
private:
	int _d1;
	char _d2;
};

//两个参数偏特化为指针类型
template <class T1, class T2>
class Data <T1*, T2*>//T1 其实还是int类型 T1才是int*类型 虽然传的int* 这点不能弄混了
{
public:
	Data() { cout << "Data<T1*, T2*>" << endl; }
private:
	T1 _d1;
	T2 _d2;
};
//两个参数偏特化为引用类型
template <class T1, class T2>
class Data <T1&, T2&>
{
public:
	Data(const T1& d1, const T2& d2)//里面的只有一个拷贝构造 确实可以偏特化 只要特定功能也是可以的
		: _d1(d1)
		, _d2(d2)
	{
		cout << "Data<T1&, T2&>" << endl;
	}
private:
	const T1& _d1;
	const T2& _d2;
};

//int main()
//{
//	JMP::array<int, 10> arr1;
//	JMP::array<int, 100> arr2;
//	Data<int, int> d1;
//	Data<int, char> d2;
//	Data<double, char> d3;//分别调用三种
//	Data<int*, int*> d4;
//	Data<int&, int&> d5(1, 2);
//
//	return 0;
//}
template<>
struct less<Date*>
{
	bool operator()( Date*& x, Date*& y) const
	{
		return *x < *y;
	}
};
int main()
{
	Date d1(2022, 7, 7);
	Date d2(2022, 7, 6);
	Date d3(2022, 7, 8);
	vector<Date> v1;
	v1.push_back(d1);
	v1.push_back(d2);
	v1.push_back(d3);
	// 可以直接排序，结果是日期升序
	sort(v1.begin(), v1.end(), less<Date>());//按照升序
	vector<Date*> v2;
	v2.push_back(&d1);
	v2.push_back(&d2);
	v2.push_back(&d3);
	// 可以直接排序，结果错误日期还不是升序，而v2中放的地址是升序
	// 此处需要在排序过程中，让sort比较v2中存放地址指向的日期对象
	// 但是走Less模板，sort在排序时实际比较的是v2中指针的地址，因此无法达到预期
	sort(v2.begin(), v2.end(), less<Date*>());//用的库里面的less发现他并没有偏特化 ---这里我们自己偏特化一个 
	//很明显达到了效果
	return 0;
}
