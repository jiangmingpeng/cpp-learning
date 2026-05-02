#define _CRT_SECURE_NO_WARNINGS
#include "Date.h"
//检查输入是否合法
bool Date::CheckDate()
{
	if (_month < 1 || _month > 12|| _day < 1 || _day > GetMonthDay(_year, _month))
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Date::DatePrint()const
{
	cout << "年:" << _year << " 月:" << _month << " 日:" << _day << endl;
}
//全缺省的默认构造函数
Date::Date(int year, int month, int day)
{
	_year = year;
	_month = month;
	_day = day;
	if (!CheckDate())
	{
		cout << "非法日期->" << *this;
	}
}
//获取某月多少天
int Date::GetMonthDay(int year, int month)
{
	assert(month > 0 && month < 13);
	int MonthDayarr[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
	{
		return 29;
	}
	else
	{
		return MonthDayarr[month];
	}
}
//计算+多少天后的日期--计算数本身也改变
Date& Date::operator+=(int day)
{
	if (day < 0)
	{
		return *this -= -day;
	}
	_day += day;
	while (_day > GetMonthDay(_year, _month))
	{
		_day -= GetMonthDay(_year,_month);
		_month++;
		if (_month == 13)
		{
			_month = 1;
			_year++;
		}
	}
	return *this;
}
//计算+多少天后的日期--计算数本身不改变
Date Date::operator+(int day)const
{
	Date temp(*this);
	temp += day;//调用赋值运算重载符 运算符后面的 其实就是他传的参数
	return temp;
}
//计算-多少天前的日期--计算数本身也改变
Date& Date::operator-=(int day)
{
	if (_day < 0)
	{
		return *this += -day;
	}
	_day -= day;
	while (_day <= 0)
	{
		_month--;
		if (_month == 0)
		{
			_year--;
			_month=12;
		}
		_day += GetMonthDay(_year, _month);
	}
	return *this;
}

//计算-多少天前的日期--计算数本身不改变
Date Date::operator-(int day)const
{
	Date temp(*this);
	temp -= day;
	return temp;
}

//计算前置++
Date& Date::operator++()
{
	(*this)+=1;
	return *this;
}
//计算后置++
Date Date::operator++(int)
{
	Date temp(*this);
	*this += 1;
	return temp;
}
//计算前置--
Date& Date::operator--()
{
	*this-=1;
	return *this;
}

//计算后置--
Date Date::operator--(int)
{
	Date temp(*this);
	*this -= 1;
	return temp;
}
//日期大小比较
bool Date::operator==(const Date& d) const
{
	return _year == d._year && _month == d._month && _day == d._day;
}
bool Date::operator!=(const Date& d) const
{
	return !(*this==d);
}
bool Date::operator<(const Date& d) const
{
	if (_year < d._year)
	{
		return true;
	}
	else if (_year == d._year && _month < d._month)
	{
		return true;
	}
	else if (_year == d._year && _month == d._month && _day < d._day)
	{
		return true;
	}
	else
		return false;
}
bool Date::operator<=(const Date& d) const
{
	return *this < d || *this == d;
}
bool Date::operator>(const Date& d) const
{
	return !(*this < d) &&* this != d;
}
bool Date::operator>=(const Date& d) const
{
	return *this > d || *this == d;
}

//计算日期差值
int Date::operator-(const Date& d) const
{
	Date max = *this;//这里是一种拷贝 max(*this);
	Date min = d;
	if (d > max)//这是用的运算符重载做的比较
	{
		max = d;
		min = *this;
	}
	int n = 0;
	while (min != max)
	{
		min++;
		n++;
	}
	return n;
}
//输出输入运算符的重载 目的是让对象也能被输入输出
ostream& operator<<(ostream& out, const Date& d)
{
	out << d._year << "年" << d._month << "月" << d._day << "日" << endl;
	return out;
}
istream& operator>>(istream& in, Date& d)
{
	while (1)
	{
		cout << "请依次输入年月日:>";
		in >> d._year >> d._month >> d._day;
		if (d.CheckDate())
		{
			break;
		}
		else
		{
			cout << "非法日期!!请你重新输入:>"<<endl;
		}
	}
	return in;
}