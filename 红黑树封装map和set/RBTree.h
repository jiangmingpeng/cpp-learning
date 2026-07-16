#pragma once
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

enum Color
{
	RED,//代号为1
	BLACK//代号为2
};


template<class T>
class RBTreeNode
{

public:
	RBTreeNode(const T& data)
		:_data(data)
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
	{	}

	T _data;

	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Color _col;
};

template <class T, class Ref, class Ptr>
class Iterator
{
public:
	typedef RBTreeNode<T> Node;
	typedef Iterator<T, Ref, Ptr> Self;

	Iterator(Node* node, Node* root)
		:_node(node)
		, _root(root)
	{	}

public:

	Ref operator* ()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(operator*());//复用*反而 能够保证是在操作同一份数据
	}

	bool operator==(const Self& it) const
	{
		return _node == it._node;
	}

	bool operator!=(const Self& it) const
	{
		return _node != it._node;
	}

	Self& operator++()
	{
		assert(_node != nullptr);
		if (_node->_right)//右不为空 下一个节点就是 此右子树的 最左节点
		{
			Node* leftMost = _node->_right;
			while (leftMost->_left)
			{
				leftMost = leftMost->_left;//找到左子树最小节点
			}
			_node = leftMost;
		}
		else//右为空 检查上一个父亲节点是祖父节点的左还是右节点--左则_node = parent 右则往上一直走 直到是上一个节点的左节点或者是根节点
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && parent->_right == cur)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}

		return *this;
	}
	Self operator++(int)
	{
		Self temp = *this;
		++(*this);
		return temp;//传的是旧的this内容
	}

	Self& operator--()// 左 中 右--》右 中 左
	{
		if (_node == nullptr)
		{
			Node* cur = _root;

			while (cur && cur->_right)//加判空 防止空树
			{
				cur = cur->_right;
			}
			_node = cur;
			return *this;
		}

		if (_node->_left)//左不为空 下一个节点就是 此左子树的 最右节点
		{
			Node* rightMin = _node->_left;
			while (rightMin->_right)
			{
				rightMin = rightMin->_right;//找到右子树最大节点
			}
			_node = rightMin;
		}
		else//左为空 检查上一个父亲节点是祖父节点的左还是右节点--右则_node = parent 右则往上一直走 直到是上一个节点的左节点或者是根节点
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent && parent->_left == cur)
			{
				cur = parent;
				parent = cur->_parent;
			}
			_node = parent;
		}

		return *this;
	}
	Self operator--(int)
	{
		Self temp = *this;
		--(*this);
		return temp; //传的是旧的this内容
	}


private:
	Node* _root;
	Node* _node;
};

template<class K, class T,class KeyofT>
class RBTree
{
public:
	typedef RBTreeNode<T> Node;
	typedef Iterator<T, T&, T*> iterator;
	typedef Iterator<T, const T&, const T*> const_iterator;
public:
	//强制默认构造
	RBTree() = default;
	// 析构函数
	~RBTree()
	{
		_Destroy(_root);
	}

	// 拷贝构造（深拷贝）
	RBTree(const RBTree& other)
		: _root(nullptr)
		, _size(other._size)
	{
		_root = _Copy(other._root);
	}

	// 赋值运算符（深拷贝）
	RBTree& operator=(const RBTree& other)
	{
		if (this != &other)
		{
			_Destroy(_root);
			_root = _Copy(other._root);
			_size = other._size; 
		}
		return *this;
	}

	size_t Size() const
	{
		return _size;
	}
	bool Empty() const
	{
		return _root == nullptr;
	}
	iterator begin()
	{
		Node* cur = _root;
		if (cur == nullptr)//为空树的判断
		{
			return iterator(nullptr,_root);
		}
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return iterator(cur,_root);
	}
	const_iterator begin() const//最后不会改变值的函数 后面记得加const保证代码健壮性 如果是const版本的 函数那就是务必要加上去的
	{
		Node* cur = _root;
		if (cur == nullptr)//为空树的判断
		{
			return const_iterator(nullptr,_root);
		}
		while (cur->_left)
		{
			cur = cur->_left;
		}
		return const_iterator(cur,_root);
	}
	iterator end()
	{
		return iterator(nullptr,_root); //end() 不是一个“有效节点”，它只是一个哨兵，用于表示遍历的终点
	}
	const_iterator end() const
	{
		return const_iterator(nullptr,_root); //end() 不是一个“有效节点”，它只是一个哨兵，用于表示遍历的终点
	}
public:

	KeyofT kot;

	iterator Find(const K& key)
	{
		return _Find(_root,key);
	}
	const_iterator Find(const K& key) const
	{
		return _Find(_root,key);
	}

	pair<iterator,bool> Insert(const T& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			_root->_col = BLACK;
			++_size;
			return {iterator(_root,_root),true};
		}
		//空树插入情况单独考虑
		Node* cur = _root;
		Node* parent = nullptr;

		while (cur)
		{
			if (kot(cur->_data) < kot(key))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(cur->_data) > kot(key))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return { iterator(cur,_root),false };
		}
		//循环结束 说明已经找到需要插入的位置
		cur = new Node(key);
		cur->_col = RED;
		Node* newnode = cur;
		if (kot(parent->_data) < kot(cur->_data))
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;//前面也只是 对于父亲的指针做了更改

		//确定cur的是父亲节点左还是右
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;

			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else//叔叔节点不存在或者节点颜色为黑的情况--这意味着红色节点连续且无法通过变色直接解决 需要旋转
				{
					if (cur == parent->_left)//从整体上来看 用特殊情况替代一般情况
					{
						RotateR(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						RotateL(parent);
						RotateR(grandfather);

						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;

				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						RotateL(grandfather);

						cur->_col = RED;
						grandfather->_col = BLACK;
					}
					else
					{
						RotateL(grandfather);
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					break;
				}
			}
		}
		++_size;
		_root->_col = BLACK;//最后把_root 的颜色置为黑 肯定没问题
		return { iterator(newnode,_root),true };
	}
	bool IsBalance()
	{
		if (_root == nullptr)
		{
			return true;
		}

		if (_root->_col == RED)//根节点必须为黑
		{
			return false;
		}

		int refNum = 0;
		Node* cur = _root;

		while (cur)
		{
			if (cur->_col == BLACK)//检查某一条路途的黑色节点个数 作为参考数目
			{
				++refNum;
			}

			cur = cur->_left;
		}

		return check(_root,0,refNum);
	}
private://用来内部调用
	bool check(Node* root, int blackNum, const int refNum)
	{
		// 前序遍历走到空时，意味着⼀条路径走完了//走到空再检查 颜色是否会出现问题
		if (root == nullptr)
		{
			if (refNum != blackNum)
			{
				cout << "存在黑色结点的数量不相等的路径" << endl; 
				return false;
			}
			return true;
		}

		// 检查孩子不太方便，因为孩子有两个，且不一定存在，反过来检查父亲就方便多了
		if (root->_col == RED && root->_parent->_col == RED)
		{
			//cout << root->_kv.first << "存在连续的红⾊结点" << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			blackNum++;
		}
		return check(root->_left, blackNum, refNum)
			&& check(root->_right, blackNum, refNum);


	}
	void _Destroy(Node* root)
	{
		if (root == nullptr)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	// 递归拷贝节点（深拷贝）
	Node* _Copy(Node* root)
	{
		if (root == nullptr)
			return nullptr;
		Node* newNode = new Node(root->_data);
		newNode->_col = root->_col;
		newNode->_left = _Copy(root->_left);
		if (newNode->_left)
			newNode->_left->_parent = newNode;
		newNode->_right = _Copy(root->_right);
		if (newNode->_right)
			newNode->_right->_parent = newNode;
		return newNode;
	}
	iterator _Find(Node* root,const K& key)
	{
		Node* cur = root;

		while (cur)
		{
			if (key> kot(cur->_data))
			{
				cur = cur->_right;
			}
			else if (key < kot(cur->_data))
			{
				cur = cur->_left;
			}
			else
			{
				return iterator(cur, _root);//构造一个迭代器 需要传的参数 这里要自己去参考迭代器的构造函数
			}
		}
		return iterator(nullptr,_root);

	}
	const_iterator _Find(Node* root,const K& key) const
	{
		Node* cur = root;

		while (cur)
		{
			if (key> kot(cur->_data))
			{
				cur = cur->_right;
			}
			else if (key < kot(cur->_data))
			{
				cur = cur->_left;
			}
			else
			{
				return const_iterator(cur, _root);//构造一个迭代器 需要传的参数 这里要自己去参考迭代器的构造函数
			}
		}
		return const_iterator(nullptr,_root);

	}

	void RotateR(Node* parent)//没必要加& 加了后续不使用的倒也不影响
	{
		//保存数据
		Node* parentParent = parent->_parent;//传过来的也有可能是子树 所以pP还有可能存在的 就算是不存在也是nullptr
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		//连接数据
		subL->_right = parent;
		parent->_parent = subL;
		subL->_parent = parentParent;//双向链接不要搞忘了

		if (parentParent)//需要考虑 parent可能是parentParent的左或者右 同样需要分情况
		{
			if (parent == parentParent->_left)
				parentParent->_left = subL;
			else
				parentParent->_right = subL;
		}
		else
		{
			_root = subL;//如果parent是根节点 跟新根
		}


		// 这里要无条件赋值
		parent->_left = subLR;//是空的也没关系 就像手动置空一样
		if (subLR)
		{
			subLR->_parent = parent;
		}
		else
		{
			parent->_left = nullptr; // 显式置空，防止残留
		}
	}

	void RotateL(Node* parent)
	{
		//保存数据
		Node* parentParent = parent->_parent;//传过来的也有可能是子树 所以pP还有可能存在的 就算是不存在也是nullptr
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		//连接数据
		subR->_left = parent;
		parent->_parent = subR;
		subR->_parent = parentParent;//双向链接不要搞忘了

		if (parentParent)//需要考虑 parent可能是parentParent的左或者右 同样需要分情况
		{
			if (parent == parentParent->_left)
				parentParent->_left = subR;
			else
				parentParent->_right = subR;
		}
		else
		{
			_root = subR;//如果parent是根节点 跟新根
		}


		// 这里要无条件赋值
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		else
		{
			parent->_right = nullptr;   // 显式置空，防止残留
		}
	}
private:
	Node* _root = nullptr;
	size_t _size = 0;
};

