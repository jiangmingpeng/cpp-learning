#pragma once
#include <iostream>


//迭代器实现 是为了什么 复用了什么 围绕什么框架展开  功能具体有哪些 细节处理 const 非const实现  
template<class iterator,class Ref,class Ptr>//我还寻思着这个正向迭代器应该怎么来 实施模板传即可解决问题
class reverseiterator
{
public:
	typedef reverseiterator<iterator, Ref, Ptr> Self;//需要const_reverse_iterator 迭代起也要传const_iterator
public:
	reverseiterator(iterator it) //临时对象具有常性 所以不能写成iterator& it 否则出现权限放大
		:_it(it)
	{ }
	Ref operator*()//返回引用类型可以修改 const版本也可以同时存在---按道理来说这个错误要自己发现
	{
		iterator temp = _it;
		temp--;
		//如果在rbegin中 本应该指向此范围里的最后一个元素的后一个位置 实际指向最后一个元素
		///为了实现这个效果在复用时不得不--得到
		//rend也是一样的应该指向第一个元素 而实际上指向第一个元素的前一个位置 所以不得不--
		//为什么不在反向中进行调整操作呢 正是因为想在使用时就已经达到目的
		return *temp;
	}
	Ptr operator->()
	{
		return &(operator*());//这个直接调用内部函数  倒也没什么问题 所以是支持的
	}	
	Self& operator++()
	{
		_it--;
		return *this;//返回当前迭代器 而不是原来的正向迭代器
	}
	Self operator++(int)
	{
		Self temp = _it;//写成temp(_it)道理是一样的 同样会调用构造函数 这是在实例化阶段 注意阶段使用可能出现的特殊情况
		_it--;
		return temp;
	}
	Self& operator--()
	{
		_it++;
		return *this;
	}
	Self operator--(int)
	{
		Self temp = _it;
		_it++;
		return temp;
	}
	
	bool operator==(const Self& it) const//既然要比较 那么肯定有参数用来比较
	{
		return _it==it._it;//转化为正向迭代器的判断 事实是一样的方法 所以直接复用
	}
	bool operator!=(const Self& it) const
	{
		return _it != it._it;
	}
private:
	iterator _it;
};


