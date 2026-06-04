#pragma once
using namespace std;


class Date
{
public:
	Date(const size_t& y,const size_t& m,const size_t& d)
		:_year(y)
		,_month(m)
		,_day(d)
	{ }
	Date(const Date& x)
		:_year(x._year)
		,_month(x._month)
		,_day(x._day)
	{ }
	bool operator<(const Date&x ) const
	{
		if (_year < x._year)	return true;
		else if (_year == x._year && _month < x._month)	return true;
		else if (_year == x._year && _month == x._month && _day < x._day)	return true;
		return false;
	}
private:
	size_t _year = 0;
	size_t _month = 0;
	size_t _day = 0;
};




