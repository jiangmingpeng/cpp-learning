#pragma once
#include <stack>
#include <queue>
#include <iostream>
#include <deque>

using  namespace std;
//强烈建议将不修改对象状态的成员函数声明为 const。这样做的好处包括：

//允许 const 对象调用该函数。------关键是这一点 预防有const对象要使用 让他们一起用

//明确表达函数的只读意图，提高代码可读性。

//帮助编译器进行优化，并防止意外修改成员变量。

//养成这个习惯会让你的代码更健壮、更符合 C++ 最佳实践


namespace JMP1
{
	template <class T,class Container = deque<T>>
	class stack
	{
	public:
		stack(const Container& ctnr = Container())
			:_con(ctnr)
		{

		}
		bool empty() const
		{
			return _con.empty();
		}
		void push(const T& data)
		{
			_con.push_back(data);
		}
		void pop()
		{
			_con.pop_back();
		}
		T& top()
		{
			return _con.back();
		}
		const T& top() const
		{
			return _con.back();
		}
		void swap(stack<T>& x) 
		{
			std::swap(_con, x._con);
		}
		size_t size() const
		{
			return _con.size();
		}
	private:
		Container _con;
	};
	
};



namespace JMP2
{
	template <class T,class Container = deque<T>>
	class queue
	{
	public:
		queue(const Container& ctnr = Container())
			:_con(ctnr)
		{

		}
		bool empty() const
		{
			return _con.empty();
		}
		size_t size() const
		{
			return _con.size();
		}
		T& front()
		{
			return _con.front();
		}
		const T& front() const 
		{
			return _con.front();
		}
		T& back() 
		{
			return _con.back();
		}
		const T& back() const 
		{
			return _con.back();
		}
		void push(const T& data )
		{
			_con.push_back(data);
		}
		void pop()
		{
			_con.pop_front();
		}
		void swap(queue<T>& x)
		{
			std::swap(_con, x._con);
		}
	private:
		Container _con;
	};
};

namespace JMP3
{
	template<class T>
	class less
	{
	public:
		bool operator()(const T& x,const T& y) const//每次写完成员函数都要考虑 const 是否可以加 应该成为肌肉记忆
		{
			return x < y;
		}
	};
	template<class T>
	class Greater
	{
	public:
		bool operator()(const T& x,const T& y) const
		{
			return x > y;
		}
	};
	template<class T, class Container = vector<T>, class Compare = less<T>>//仿函数还没加进去
	class priority_queue//默认优先级是大堆
	{
	public:
		//priority_queue() = default;

		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last, const Compare& comp = Compare())//实现迭代器构造函数
			:_comp(comp)//初始化列表的这个细节不能忘
		{
			Container v(first, last);
			if (!v.empty())//当size为0时出现 溢出情况 若写的条件类型是size_t就会导致无限循环
			{
				for (int i = (v.size() - 1 - 1) / 2; i >= 0; i--)//其实可以根据传什么参数来 反推前面的代码可能是什么样子
				{
					adjust_down(v, i);
				}
			}
			_con = v;	
		}
		priority_queue( const Container& ctnr = Container(),const Compare & comp = Compare())
			:_con(ctnr)
			,_comp(comp)
		{ }
		bool empty() const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}

		T& top()
		{
			return _con.front();
		}
		const T& top() const
		{
			return _con.front();
		}
		void adjust_up(Container &hp,size_t child)
		{
			size_t parent = (child - 1) / 2;
			while (child>0)
			{
				if (_comp(hp[parent], hp[child]))
				{
					std::swap(hp[child], hp[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		void push(const T& data)
		{
			_con.push_back(data);
			adjust_up(_con, _con.size()-1);
		}
		void adjust_down(Container& hp, size_t parent)
		{
			size_t child = parent * 2 + 1;
			while (child < hp.size())
			{
				if (child + 1 < hp.size() && _comp(hp[child], hp[child + 1]))	++child;
				if (_comp(hp[parent],hp[child] ))
				{
					std::swap(hp[child], hp[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		void pop()
		{
			std::swap(_con.front(),_con.back());
			_con.pop_back();
			adjust_down(_con,0);
		}
		void swap(priority_queue<T>& x)
		{
			std::swap(_con, x._con);
		}
	private:
		Container _con;
		Compare _comp;
	};
};