#pragma once

#include "Hashtable.h"

template <class K,class V, class Hash = HashFunc<K>>//这个哈希函数 从键值中取值
class unordered_map
{
	struct MapKeyofT
	{
		const K& operator()(const pair<const K, V>& kv) const
		{
			return kv.first;
		}
	};
public:
	typedef typename HashTable<K, pair<const K,V>, MapKeyofT, Hash>::iterator iterator;
	typedef typename HashTable<K, pair<const K,V>, MapKeyofT, Hash>::const_iterator const_iterator;
public:
	pair<iterator,bool> insert(const pair<K, V>& kv) { return  _t.Insert(kv); }//具体插入什么根据具体容器决定
	iterator find(const K& key) { return _t.Find(key); }
	bool erase(const K& key) { return _t.Erase(key); }
	iterator begin() { return _t.Begin(); }
	const_iterator begin() const { return _t.Begin(); }
	iterator end() { return _t.End(); }
	const_iterator end() const { return _t.End(); }
	V& operator[](const K& key)//写这种接口的时候 卡到先想想功能 如何解决
	{
		pair<iterator, bool> ret = insert({ key, V()});
		return ret.first->second;//迭代器指的是节点 而节点就是一个pair类型 所以这里嵌套了一个pair
	}
private:
	HashTable < K, pair<const K, V>, MapKeyofT,Hash> _t;
};