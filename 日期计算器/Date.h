#pragma once
#include<iostream>
#include <assert.h>
using namespace std;
class Date
{
	// 友元函数声明
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:

	//全缺省的默认构造函数
	Date(int year = 1, int month = 1, int day = 1);
	//检查输入是否合法
	bool CheckDate();
	//获取某月多少天
	int GetMonthDay(int year, int month);
	//计算+多少天后的日期--计算数本身也改变
	Date& operator+=(int day);
	//计算+多少天后的日期--计算数本身不改变
	Date operator+(int day)const;
	//计算-多少天前的日期--计算数本身也改变
	Date& operator-=(int day);
	//计算-多少天前的日期--计算数本身不改变
	Date operator-(int day)const;
	//计算前置++
	Date& operator++();
	//计算后置++
	Date operator++(int);
	//计算前置--
	Date& operator--();
	//计算后置--
	Date operator--(int);
	//大小比较
	bool operator==(const Date& d) const;//只要不改变调用对象的函数都建议加const
	//加 const：表示该成员函数是常量成员函数，承诺不会修改任何成员变量（mutable 除外）。
	//可以被 const 对象调用，也可以在非 const 对象上调用。
	//不加 const：只能被非 const 对象调用。
	//如果有一个 const Date 对象，则无法使用 == 进行比较，会导致编译错误。
	bool operator!=(const Date& d) const;
	bool operator<(const Date& d) const;
	bool operator<=(const Date& d) const;
	bool operator>(const Date& d) const;
	bool operator>=(const Date& d) const;
	//计算日期差值
	int operator-(const Date& d) const;

	//打印日期
	void DatePrint()const;
	//显化拷贝构造函数----编译器的默认拷贝已经够用 这里更多的是运用深拷贝
	Date(const Date& d)
	{
		this->_year = d._year;
		this->_month = d._month;
		this->_day = d._day;
	}
private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& out, const Date& d);
istream& operator>>(istream& in, Date& d);