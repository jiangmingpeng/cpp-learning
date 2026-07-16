#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;
template <class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return size_t(key);
	}
};
template<>//BKDR 哈希
struct HashFunc<string>//仿函数特化string作为键值
{
	size_t operator()(const string& key) const//要对 const敏感点 不改变值的 尽量都加上const
	{
		size_t _num = 0;
		for (auto e : key)
		{
			_num *= 33;
			_num += e;
		}
		return _num;
	}
};
//每个哈希桶的结构---先写整形 再加其他类型的 这里以string为例 其他的思路大致是一样的 主要是找出唯一性
template <class T>
struct HashNode
{
	T _data;
	HashNode<T>* _next;

	HashNode(const T& data)
		:_data(data)
		, _next(nullptr)
	{	}
};

template <class K, class T, class KeyOfT, class Hash>
class HashTable;//有模板的 类的前置声明

template <class K,class T,class Ref,class Ptr,class KeyOfT,class Hash>
struct HTIterator
{
	friend class HashTable<K, T, KeyOfT, Hash>;

	typedef HashNode<T>  Node;
	typedef HTIterator<K, T, Ref, Ptr, KeyOfT, Hash> Self;
	typedef HashTable<K, T, KeyOfT, Hash>  HT;

	Node* _node;//迭代器指向的节点指针
	HT* _ht;//
	size_t _bucket;

	HTIterator(Node* node,HT* ht,size_t bucket)
		:_node(node)
		,_ht(ht)
		,_bucket(bucket)
	{	}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(_node->_data);
	}

	Self& operator++()//前置++
	{
		if (_node && _node->_next)
		{
			_node = _node->_next;
			return *this;
		}
		if (_node == nullptr)
		{
			return *this; // 或者 assert(false)
		}	
		size_t nextBucket = _bucket + 1;// 从当前桶的下一个开始查找
		while (nextBucket < _ht->_tables.size())
		{
			if (_ht->_tables[nextBucket])
			{
				_node = _ht->_tables[nextBucket];
				_bucket = nextBucket;
				return *this;
			}
			++nextBucket;//没有节点的桶跳过继续++
		}
		// 后面没有非空桶，直接返回 end()
		_node = nullptr;
		_bucket = _ht->_tables.size(); //把桶索引置为最大 size 表示结束end
		return *this;
	}
	//Self& operator++()//前置++
	//{
	//	if (_node->_next)
	//	{
	//		_node = _node->_next;
	//	}
	//	else//说明要跳到下一个有节点的桶里去
	//	{
	//		size_t hashi = Hash()(KeyOfT()(_node->_data)) % _ht->_tables.size();//利用匿名对象直接创建再使用 不用额外创建 生命周期就只有在这一行
	//		++hashi;
	//		while (hashi != _ht->_tables.size())
	//		{
	//			if (_ht->_tables[hashi])
	//			{
	//				_node = _ht->_tables[hashi];
	//				break;
	//			}
	//			hashi++;
	//		}
	//		if (hashi == _ht->_tables.size())
	//		{
	//			_node = nullptr;//相当于走到end(); ---因为end本身确实是一个结束标志
	//		}
	//	}
	//	return *this;
	//}
	Self operator++(int)
	{
		Self temp = *this;
		++(*this);
		return temp;
	}

	Self& operator--()//前置--
	{
		// 如果是 end() (_node == nullptr)退到最后一个元素
		if (_node == nullptr)
		{
			for (size_t i = _ht->_tables.size(); i > 0; --i)
			{
				size_t bucket = i - 1;
				if (_ht->_tables[bucket])//找到一个非空桶
				{
					// 跳到该桶的最后一个节点
					Node* cur = _ht->_tables[bucket];
					while (cur->_next) cur = cur->_next;
					_node = cur;
					_bucket = bucket;
					return *this;
				}
			}
			_node = nullptr;
			_bucket = 0;
			return *this;
		}

		// 不是桶的头节点
		if (_node != _ht->_tables[_bucket])
		{
			// 从桶头开始遍历，找到前一个节点
			Node* cur = _ht->_tables[_bucket];
			while (cur->_next != _node) cur = cur->_next;
			_node = cur;// _bucket 不变			
			return *this;
		}

		//当前节点是桶头 需要向前找上一个非空桶
		for (size_t i = _bucket; i > 0; --i)
		{
			size_t bucket = i - 1;
			if (_ht->_tables[bucket])
			{
				// 跳到该桶的最后一个节点
				Node* cur = _ht->_tables[bucket];
				while (cur->_next) cur = cur->_next;
				_node = cur;
				_bucket = bucket;
				return *this;
			}
		}

		//没有上一个桶 说明当前是第一个元素 则退回 end()
		_node = nullptr;
		_bucket = 0;
		return *this;
	}
	Self operator--(int)
	{
		Self temp = *this;
		--(*this);
		return temp;
	}

	bool operator==(const Self& s) const//是否相等 看节点地址即可确定
	{
		return _node == s._node;
	}
	 
	bool operator!=(const Self& s) const
	{
		return _node != s._node;
	}
	//迭代器哪有什么比大小 要清楚自己在写什么类
};


//哈希表的结构
template <class K,class T,class KeyOfT, class Hash = HashFunc<K>>//模板参数多了 要注意区别 使用的时候分别可能对应的是什么  不要混乱了
class HashTable
{
	template<class K, class T, class Ref, class Ptr, class KeyOfT, class Hash>
	friend struct HTIterator;//只有这一个需要用的模板 友元这样用就可以

	inline unsigned long __stl_next_prime(unsigned long n)
	{
		static const int __stl_num_primes = 28;
		static const unsigned long __stl_prime_list[__stl_num_primes] =
		{
			53, 97, 193, 389, 769,
			1543, 3079, 6151, 12289, 24593,
			49157, 98317, 196613, 393241, 786433,
			1572869, 3145739, 6291469, 12582917, 25165843,
			50331653, 100663319, 201326611, 402653189, 805306457,
			1610612741, 3221225473, 4294967291
		};
		const unsigned long* first = __stl_prime_list;
		const unsigned long* last = __stl_prime_list +__stl_num_primes;
		const unsigned long* pos = lower_bound(first, last, n);
		return pos == last ? *(last - 1) : *pos;
	}
public:
	typedef HashNode<T> Node;
	typedef HTIterator<K, T, T&, T*, KeyOfT, Hash> iterator;
	typedef HTIterator<K, T, const T&, const T*, KeyOfT, Hash> const_iterator;
public:
	pair<iterator,bool> Insert(const T& data)
	{
		KeyOfT  kot;
		HashFunc<K> ht;
		//先扩容在处理边界情况
		if (_n == _tables.size())
		{
			//扩容
			vector<Node*> newtables(__stl_next_prime(_tables.size() + 1));//只传数字 走的是第二个构造函数 大小为n 其他默认 空顺序表

			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
					
				while (cur)
				{
					Node* next = cur->_next;

					int hashi = ht(kot(cur->_data)) % newtables.size();
					cur->_next = newtables[hashi];
					newtables[hashi] = cur;

					cur = next;
				}
				_tables[i] = nullptr;//这个桶的节点被摘完了 所以把这个桶直接置空

			}
			newtables.swap(_tables);//然后 把原生哈希表的指针指向新的哈希表 至此结束扩容工作
		}
		auto it = Find(kot(data));//it本身是一个迭代器 所以这里的返回值不是{iterator(....),false};
		if (it != End())
		{
			return { it,false };
		}
		//空间足够时 自然插入
		int hashi = ht(kot(data)) % _tables.size();//这个表的每个桶 的桶顶都是第一个节点的指针------相当于一个指针数组
		Node* newNode = new Node(data);
		newNode->_next = _tables[hashi];
		_tables[hashi] = newNode;
		_n++;

		return { iterator(newNode,this,hashi),true };
	}

	iterator Find(const K& key)
	{
		KeyOfT kot;
		HashFunc<K> ht;
		int hashi = ht(key) % _tables.size();//注意桶的位置是已经由需要查找的值已经确定下来了--就可以不在看其他桶的位置了
		Node* cur = _tables[hashi];
		while (cur)
		{
			Node* next = cur->_next;
			if (kot(cur->_data) == key)
			{
				return iterator(cur,this,hashi);
			}
			cur = next;
		}
		return iterator(nullptr, this, 0);
	}

	bool Erase(const K& key)
	{
		KeyOfT kot;
		HashFunc<K> ht;
		int hashi = ht(key) % _tables.size();//注意桶的位置是已经由需要查找的值已经确定下来了--就可以不在看其他桶的位置了
		Node* cur = _tables[hashi];
		Node* prev = nullptr;
		while (cur)
		{

			Node* next = cur->_next;
			if (kot(cur->_data) == key)
			{
				if (prev == nullptr)
				{
					_tables[hashi] = cur->_next;
				}
				else
				{
					prev->_next = cur->_next;
				}
				delete cur;
				--_n;
				return true;
			}
			prev = cur;
			cur = next;
		}
		return false;
	}

	iterator Begin()
	{
		for (size_t i = 0; i < _tables.size(); i++)
		{
			if (_tables[i])
			{
				return iterator(_tables[i], this, i);
			}
		}
		return End();
	}
	const_iterator Begin() const
	{
		for (size_t i = 0; i < _tables.size(); i++)
		{
			if (_tables[i])
			{
				return const_iterator(_tables[i], this, i);
			}
		}
		return End();
	}

	iterator End()
	{
		return iterator(nullptr, this, 0);
	}
	const_iterator End() const
	{
		return const_iterator(nullptr, this, 0);
	}


	HashTable()
		:_tables(__stl_next_prime(0))
		,_n(0)
	{	}
	HashTable(const HashTable& HT)
		:_tables(HT._tables.size(), nullptr)// 先把表的大小调整成和 HT 一样大
		,_n(HT._n)
	{
		for (size_t i = 0; i < HT._tables.size(); ++i)
		{
			Node* cur = HT._tables[i]; 
			//这位置有桶 就直接对这个位置
			while (cur)
			{
				// 创建新节点 深拷贝数据
				Node* newNode = new Node(cur->_data); 
				newNode->_next = nullptr;

				Node* next = cur->_next;
				// 头插
				newNode->_next = _tables[i];
				_tables[i] = newNode;
					
				cur = next;
			}
		}
	}
	~HashTable()
	{
		//先析构链表 再释放vector
		for (size_t i = 0; i < _tables.size(); i++)
		{
			Node* cur = _tables[i];

			while (cur)
			{
				Node* next = cur->_next;

				delete cur;
				cur = next;
			}
			_tables[i] = nullptr;//这个桶的节点被摘完了 所以把这个桶直接置空

		}
	}
private:
	vector<Node*> _tables;
	size_t _n = 0;
};

