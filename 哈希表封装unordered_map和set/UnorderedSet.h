#pragma once

#include "Hashtable.h"

template <class K, class Hash = HashFunc<K>>
class unordered_set
{
	struct SetKeyofT
	{
		const K& operator()(const K& key) const
		{
			return key;
		}
	};
public:
	typedef typename HashTable<K, const K, SetKeyofT, Hash>::iterator iterator;
	typedef typename HashTable<K, const K, SetKeyofT, Hash>::const_iterator const_iterator;
	
public:
	pair<iterator,bool> insert(const K& key){return  _t.Insert(key);}//具体插入什么根据具体容器决定
	iterator find(const K& key) { return _t.Find(key); }
	bool erase(const K& key) { return _t.Erase(key); }
	iterator begin() { return _t.Begin(); }
	const_iterator begin() const { return _t.Begin(); }
	iterator end() { return _t.End(); }
	const_iterator end() const { return _t.End(); }
private:
	HashTable<K, const K, SetKeyofT,Hash> _t;//前面两个是重复的 之所以这么设计是因为 要兼顾map的实现
	//这个Hash虽然有缺省参数 但依然要传 如果后面要传新的HashFunc可能会用的到 一直从外至内
};