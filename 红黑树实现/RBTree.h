#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum Color
{
	RED,//代号为1
	BLACK//代号为2
};


template<class K, class V>
class RBTreeNode
{

public:
	RBTreeNode(const pair<K,V>& kv)
		:_kv(kv)
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
	{	}

	pair<K, V> _kv;
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	Color _col;
};

template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K,V> Node;
public:

	void InOrder()
	{
		_InOrder(_root);
	}

	bool Find(const K& key)
	{
		return _Find(_root,key);
	}

	bool Insert(const pair<K,V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		//空树插入情况单独考虑
		Node* cur = _root;
		Node* parent = nullptr;

		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}
		//循环结束 说明已经找到需要插入的位置
		cur = new Node(kv);
		cur->_col = RED;
		if (parent->_kv.first < cur->_kv.first)
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
		_root->_col = BLACK;//最后把_root 的颜色置为黑 肯定没问题
		return true;
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
			cout << root->_kv.first << "存在连续的红⾊结点" << endl;
			return false;
		}
		if (root->_col == BLACK)
		{
			blackNum++;
		}
		return check(root->_left, blackNum, refNum)
			&& check(root->_right, blackNum, refNum);


	}

	bool _Find(Node* root,const K& key)
	{
		Node* cur = root;

		while (cur)
		{
			if (key > cur->_kv.first)
			{
				cur = cur->_right;
			}
			else if (key < cur->_kv.first)
			{
				cur = cur->_left;
			}
			else
			{
				return true;
			}
		}
		return false;

	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first<<":"<<root->_kv.second<< " ";
		_InOrder(root->_right);
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
};