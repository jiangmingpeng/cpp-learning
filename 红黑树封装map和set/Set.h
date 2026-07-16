#pragma once
#include "RBTree.h"

namespace JMP1
{

	template <class K>
	class set
	{
		struct SetKeyofT
		{
			const K& operator()(const K& key) const
			{
				return key;
			}
		};

	public:															//要明白 typename的作用 编译器默认认为 依赖名::xxx 不是类型（而是变量或函数）
		typedef typename RBTree<K, const K, SetKeyofT>::iterator iterator;//编译器猜不出来 标准就规定 如果这确实是一个类型，必须显式地用 typename 关键字告诉编译器
		typedef typename RBTree<K, const K, SetKeyofT>::const_iterator const_iterator;
	public:
		pair<iterator, bool> Insert(const K& key)//具体插入什么根据具体容器决定
		{
			return  _rb.Insert(key);
		}

		iterator begin() { return _rb.begin(); }
		const_iterator begin() const { return _rb.begin(); }
		iterator end() { return _rb.end(); }
		const_iterator end() const { return _rb.end(); }

		iterator find(const K& key)
		{
			return _rb.Find(key);
		}
		const_iterator find(const K& key) const
		{
			return _rb.Find(key);
		}
		size_t Size() const { return _rb.Size(); }
		bool Empty() const { return _rb.Empty(); }

	private:
		RBTree < K, const K, SetKeyofT> _rb;//前面两个是重复的 之所以这么设计是因为 要兼顾map的实现
	};
}

