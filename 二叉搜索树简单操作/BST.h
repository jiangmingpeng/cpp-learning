#pragma once
#include <vector>
#include <iostream>
using namespace std;
template <class K>
struct BSTNode
{
	K _key;
	BSTNode<K>* _left;
	BSTNode<K>* _right;

	BSTNode(const K& key)
		:_key(key)
		,_left(nullptr)
		,_right(nullptr)
	{ }
};

template <class K>
class BSTree
{
	typedef BSTNode<K> Node;


public:
	void Inoder()
	{
		_Inoder(_root);
		cout << endl;
	}
	bool Insert(K key)//非递归
	{
		//构建搜索二叉树
		if (_root== nullptr)
		{
			_root = new Node(key);
			return true;//不要忘了 这个插入的函数 返回值是布尔值---需要对实时情况进行反馈
		}
		//既然到这里里了那么 根节点肯定不为空
		Node* parent = nullptr;
		Node* cur = _root;//很明显 我们需要一个cur节点用来指路的 所以它肯定是要移动的
		//既然cur会移动 那么肯定会出现边界条件 这个条件就可以给来接下来的循环使用
		//先找到位置 再来进行插入操作 这一步是准备操作

		//如果前面一步进行了插入操作 那么这个cur永远不会达到跳出条件
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
	
		cur = new Node(key);

		if (key > parent->_key)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		return true;
		//走到这 节点肯定都插入进去了
	}

	bool Find(const K& key)
	{

		Node* cur = _root;
		while (cur)
		{
			if (key > cur->_key)
			{
				cur = cur->_right;
			}
			else if (key < cur->_key)
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
	bool Erase(const K& key)
	{

		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}//一直到这里是已经找到需要删除的节点了
			else
			{
				//节点无子节点 或者只有左右其中一个子节点的删除				-----最后再看如果删除的为根节点应该如何处理父节点
				//如果删的是 根节点需要处理根节点没有父节点的情况--可以进行单独处理
				if (parent == nullptr)
				{
					// 根节点有两个孩子时，不能直接删除，应该走后面的替换逻辑
					if (cur->_left && cur->_right)
					{
						// 不处理，让后面的两个孩子的代码去处理
						// 这里不能 return，需要继续往下执行到两个孩子处理部分
					}
					else
					{
						if (cur->_right)
							_root = cur->_right;
						else
							_root = cur->_left;
						delete cur;
						return true; 
					}
				}
				//节点有两个孩子节点的删除
				Node* minRight = cur;
				Node* minRightParent = nullptr;
				if (cur->_left && cur->_right)
				{
					Node* minParent = cur;
					Node* minright = cur->_right;
					// 寻找右子树中的最小节点（即最左节点）
					while (minright->_left)
					{
						minParent = minright;
						minright = minright->_left;
					}//-----------
					// 交换值
					swap(cur->_key, minright->_key);
					// 删除 minright（它最多有一个右孩子）
					if (minParent->_left == minright)
						minParent->_left = minright->_right;
					else//右子树的根节点本身没有左孩子时，这个根节点就是最小节点，而它的父节点就是 cur，此时它是 cur 的右孩子（而不是左孩子）
						minParent->_right = minright->_right;//出现minRight 就是cur 时且此时只有一个孩子 就会跳到这里来
					delete minright;
					return true;
				}
				if (cur == parent->_right)
				{
					if (cur->_right && cur->_left == nullptr)
					{
						parent->_right = cur->_right;
						delete cur;
						return true;
					}
					else if (cur->_left && cur->_right == nullptr)
					{
						parent->_right = cur->_left;
						delete cur;
						return true;
					}
					else if (cur->_left == nullptr && cur->_right == nullptr)
					{
						if (cur == parent->_left)        //先置空 再删除节点改为左孩子判断
							parent->_left = nullptr;
						else
							parent->_right = nullptr;
						delete cur;
						return true;
					}
				}
				else
				{
					if (cur->_right && cur->_left == nullptr)
					{
						parent->_left = cur->_right;
						delete cur;
						return true;

					}
					else if (cur->_left && cur->_right == nullptr)
					{
						parent->_left = cur->_left;
						delete cur;
						return true;

					}
					else if (cur->_left == nullptr && cur->_right == nullptr)
					{
						if (cur == parent->_left)        // 改为左孩子判断
							parent->_left = nullptr;
						else
							parent->_right = nullptr;
						delete cur;
						return true;
					}
				}
				
			}
		}
		//到这里说明没有找到要删除的节点
		return false;
	}

private:
	void _Inoder(Node* root)//前序遍历二叉搜索树
	{
		if (root== nullptr)
			return;

		_Inoder(root->_left);
		cout << root->_key << " ";
		_Inoder(root->_right);

	}

	
private:
	Node* _root = nullptr;

};