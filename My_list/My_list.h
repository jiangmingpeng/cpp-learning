#pragma once
#include <iostream>
#include <assert.h>
#include <list>
#include <algorithm>
using namespace std;

namespace JMP
{
	template <class T>
	struct ListNode
	{
		ListNode(const T& data = T())
			:_data(data)
			,_prev(nullptr)
			,_next(nullptr)
		{	}
		T _data;
		ListNode<T>* _prev;
		ListNode<T>* _next;
	};//节点创建
	template <class T,class Ref, class Ptr>
	struct ListIterator //制作迭代器就要知道 迭代器在list中发挥的什么作用 分别实现什么功能
	{
		typedef ListNode<T> Node;
		typedef ListIterator<T, Ref,Ptr> Self;//其实是代表的两种 list 非const 和const 的种类 、然后分别进入两种模板构造
		Node* _node;//这里创建一个节点---目的是让这个迭代器 指向这个位置

		ListIterator(Node* node)//既然用迭代器的话 后面就会接内容 否则就是随机迭代器
			:_node(node)
		{   }
		Ref operator* ()//返回的是一个可修改值或者 不可修改 别搞错了
		{
			return _node->_data;
		}
		Ptr operator->()//当链表元素是自定义类或结构体，并且需要访问该元素的成员时，就可以自然写出 it->member
		{//自定义类型也有可能是 const对象 所以再搞一个模板用来区分它
			return &(_node->_data);
		}
		Self& operator++()
		{
			_node = _node->_next;
			return *this;//先++后放回
		}
		Self operator++(int)//后置++
		{
			Self temp(_node);//先放回后++
			_node = _node->_next;
			return temp;
		}
		Self& operator--()
		{
			_node = _node->_prev;
			return *this;//先--后放回
		}
		Self operator--(int)
		{
			Self temp(_node);//先放回后++
			_node = _node->_prev;
			return temp;
		}
		bool operator!=(const Self& it) const
		{
			return _node != it._node;
		}
		bool operator==(const Self& it) const
		{
			return _node == it._node;
		}
	};
	template <class T>
	class list
	{
		typedef ListNode<T> Node;
	public://迭代器的相关内容
		typedef ListIterator<T,T&,T*> iterator;
		typedef ListIterator<T,const T&,const T*> const_iterator;//我该如何让他一个人承担两个角色
	public://各种函数

		iterator begin()
		{
			return iterator(_head->_next);
		}
		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}
		const_iterator end() const
		{
			return const_iterator(_head);
		}

		void swap(list<T>& x)
		{
			std::swap(_head,x._head);
			std::swap(_size,x._size);
		}

		bool empty() const
		{
			return _size == 0;
		}

		void empty_init()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		list()
		{
			empty_init();
		}

		list(const list<T>& x)
		{
			empty_init();
			for (auto e : x)//x是被拷贝的list push_back是插入准备要构造的 主宾要弄清楚
			{
				push_back(e);
			}
		}
		list& operator= (list<T> x)
		{
			swap(x);
			return *this;
		}

		list(initializer_list<T> x)//用花括号初始化的那个迭代器 记得学习思路
		{
			empty_init();
			for (const T&e : x)//用auto验证一下
			{
				push_back(e);
			}
		}

		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}

		void push_front(const T& data)
		{
	/*		Node* New_node = new Node(data);
			Node* prev = _head->_next;

			prev->_prev = New_node;
			New_node->_next = prev;
			New_node->_prev = _head;
			_head->_next = New_node;
			_size++;*/
			insert(begin(), data);
		}
		void pop_front()
		{
			//assert(!empty());

			//Node* next = _head->_next->_next;//留的就是这个next 删的就是这个_head->_next

			//_head->_next = next;
			//next->_prev = _head;
			//_head->_next->_prev = nullptr;
			//_size--;
			erase(begin());
		}
		void push_back(const T& data)
		{
			//Node* New_node = new Node(data);
			//Node* tail = _head->_prev;//这个尾设置的很巧 无论是否有 有效节点 都能做到

			//tail->_next = New_node;
			//New_node->_prev = tail;
			//New_node->_next = _head;
			//_head->_prev = New_node;
			//_size++;
			insert(end(), data);
		}
		void pop_back()
		{
			//assert(!empty());
			//Node* prev = _head->_prev->_prev;//留的就是这个prev 删的就是这个_head->_prev

			//_head->_prev->_next = nullptr;
			//_head->_prev = prev;
			//prev->_next = _head;
			//_size--;
			erase(--end());//end()本身是最后一个有效位置位置的下一个 所以传这个迭代器时候要先-- 
		}
		iterator insert(iterator pos, const T& val)
		{
			Node* newnode = new Node(val);
			Node* prev = pos._node->_prev;

			prev->_next = newnode;
			newnode->_prev = prev;

			newnode->_next = pos._node;
			pos._node->_prev = newnode;

			_size++;
			return iterator(newnode);
		}
		void clear()
		{
			iterator it = begin();
			while (it!=end())
			{
				it = erase(it);//删除就是指向下一个位置
			}
		}
		iterator erase(iterator pos)
		{
			assert(!empty());
			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;
			prev->_next = next;
			next->_prev = prev;
			delete pos._node;
			_size--;
			return next;//本应如此
		}

		size_t size() const
		{
			//size_t n = 0;
			//iterator it = begin();
			//while (it != end())
			//{
			//	n++;
			//	it++;
			//}
			//return n;//由于每次添加新元素都会重新计算size
			// 那么不如直接在插入数据时进行size的操作 这样就能直接返回size的值
			return _size;
		}
	private:
		Node* _head;
		size_t _size = 0;
	};
};