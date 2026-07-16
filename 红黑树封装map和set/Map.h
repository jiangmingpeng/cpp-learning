#pragma once
#include "RBTree.h"


namespace JMP2
{

	template <class K, class V >
	class map
	{
		struct MapKeyofT
		{
			const K& operator()(const pair<const K,V>& kv) const
			{
				return kv.first;
			}
		};

	public:
		typedef typename RBTree<K, pair<const K, V>, MapKeyofT>::iterator iterator;//在类里面 取没有确定的类模板成员 要加 typename
		typedef typename RBTree<K, pair<const K, V>, MapKeyofT>::const_iterator const_iterator;
	public:

		pair<iterator,bool> insert(const pair<K, V>& kv)//具体插入什么根据具体容器决定
		{
			return  _rb.Insert(kv);
		}
		iterator begin() { return _rb.begin(); }
		const_iterator begin() const { return _rb.begin(); }
		iterator end() { return _rb.end(); }
		const_iterator end() const { return _rb.end(); }

		iterator find(const K& kv)
		{
			return _rb.Find(kv);
		}
		const_iterator find(const K& kv) const
		{
			return _rb.Find(kv);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			return ret.first->second;
		}
		size_t Size() const { return _rb.Size(); }
		bool Empty() const { return _rb.Empty(); }
	private:
		RBTree < K, pair<const K,V>, MapKeyofT> _rb;
	};
}

